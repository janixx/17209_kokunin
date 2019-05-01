#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>

#include "/usr/include/mpich/mpi.h"

inline const int NUM_DIMS = 2;
inline const int N1 = 4000;
inline const int N2 = 8000;
inline const int N3 = 12000;

using std::cout;
using std::endl;

void algorhitm(double *A, double *B, double *C, int * dims, MPI_Comm comm);

int main(int argc, char * argv[]) {
    MPI_Init(&argc, &argv);
    int size, rank, reorder; /*reorder variable for MPI_Cart_crate flag */
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n[3] = {0,0},
        p[2] = {0,0},
        dims[NUM_DIMS] = {0,0},
        periods[NUM_DIMS] = {0,0}; /*flag variable периодична ли решётка создаваемая MPI_Cart_crate */

    double *A = nullptr, *B = nullptr, *C = nullptr;
    struct timeval tv1, tv2;


    MPI_Comm comm;
    MPI_Dims_create(size, NUM_DIMS, dims);//наиболее подходящая для NUM_DIMS-мерного коммутатора структура
    MPI_Cart_create(MPI_COMM_WORLD, NUM_DIMS, dims, periods, reorder, &comm);//создаём декартову решутку

    if (rank == 0) {
        A = new double[N1 * N2];
        B = new double[N2 * N3];
        C = new double[N1 * N3]();

        for(int i = 0; i < N1; ++i)
            for(int j = 0; j < N2; ++j)
                A[N2*(i)+(j)] = i+1;
        for(int i = 0; i < N2; ++i)
            for(int j = 0; j < N3; ++j)
                B[N3*(i)+(j)] = 21+i;
    }

//    std::cout << "I'm process № " << rank
//              << "; dims[0](X) = " << dims[0]
//              << ", dims[1](Y) = " << dims[1] << ";" << std::endl;
    //MPI_Bcast(&comm,1,MPI_,0,MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);//чтобы процессы начинали выполнение в одно время
    gettimeofday(&tv1, nullptr);

    algorhitm(A, B, C, dims, comm);

    gettimeofday(&tv2, (struct timezone*)0);
    std::cout << " My rank is: " << rank << "; My time = " <<
        ((tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec) << std::endl;


    //MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0) {
//        std::cout << "Matrix A is: " << std::endl;
//        for(int i = 0; i < N1; i++) {
//            for(int j = 0; j < N2; j++)
//                printf(" %3.1f",A[N2*(i)+(j)]);
//
//            std::cout<<std::endl;
//        }
//
//        std::cout << "Matrix B is: " << std::endl;
//        for(int i = 0; i < N2; i++) {
//            for(int j = 0; j < N3; j++)
//                printf(" %3.1f",B[N3*(i)+(j)]);
//
//            std::cout<<std::endl;
//        }

//        std::cout << "Answer is: " << std::endl;
//        for(int i = 0; i < N1; i++) {
//            for(int j = 0; j < N3; j++)
//                printf(" %3.1f",C[N3*(i)+(j)]);
//
//            std::cout<<std::endl;
//        }

        delete[] A;
        delete[] B;
        delete[] C;
    }

    MPI_Comm_free(&comm);
    MPI_Finalize();
    return EXIT_SUCCESS;
}

void algorhitm(double *A, double *B, double *C, int dims[], MPI_Comm comm) {

    double *partA, *partB, *partC;
    int coords[NUM_DIMS], periods[2] = {0,0}, remains[2], rank = 1, lenPart = 0, highPart = 0;
    //координаты пр-сса в решётке, параметры для 1-мерного коммутатора(непериодчность, какая координата зануляется при создании из 2-х мерного)
    MPI_Datatype typeB, typeC, types[2];//производные типы для частей матриц Б, Ц и создания этих типов
    MPI_Comm comm2D, comm1D[2];

    int *sizeC, *dispC, *sizeB, *dispB;//смещение и длинна блоков данных в производных типах матриц Б и Ц

    MPI_Bcast(dims, 2, MPI_INT, 0, comm);//все пр-ссы узнают dims из нулевого
    int sizeX = dims[0], sizeY = dims[1];//количество полос и столбцов

    MPI_Cart_create(comm, 2, dims, periods, 0, &comm2D);//СОЗДАЁМ 2D РЕШЁТКУ
    MPI_Comm_rank(comm2D, &rank);//узнаём номер пр-сса в решётке чтобы узнать координаты в ней
    MPI_Cart_coords(comm2D, rank, 2, coords);

    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            remains[j] = (i == j);
        }
        MPI_Cart_sub(comm2D, remains, comm1D + i);//создаём 1D коммутатор из 2D
    }

    highPart = N1 / sizeX;// сколько элементов по-вертикали в полосе матрицы А
    lenPart = N3 / sizeY;// сколько элементов по горизонатли в столбцк матрицы Б

//    if (rank == 0) {
//        cout << "I'm first process; highP = "
//            << highPart << ", lenP = "
//            << lenPart << endl;
//    }
//    MPI_Barrier(comm2D);

    partA = new double[highPart * N2];
    partB = new double[N2 * lenPart];
    partC = new double[highPart * lenPart];

    if(rank == 0) {
        types[1] = MPI_UB;//разделитель

        int bLen[2] = {1, 1};//parts of typeB or typeC
        MPI_Aint sizeofdouble;
        MPI_Type_extent(MPI_DOUBLE, &sizeofdouble);//a.k.a. sizeof(double)
        MPI_Aint disp[2] = { 0, (sizeofdouble * lenPart) };//смещение блоков данных отн-о начала
        //даблы с начала, разделитель -- в конце каждого блока

        //count of vectors in memory, count doubles in one element, count elements in generally, ..
        MPI_Type_vector(N2, lenPart, N3, MPI_DOUBLE, &types[0]);
        MPI_Type_struct(2, bLen, disp, types, &typeB);//структура -- сначала вектор из даблов, потом разделитель
        MPI_Type_commit(&typeB);

        dispB = new int[sizeX];
        sizeB = new int[sizeX];
        for(int i = 0; i < sizeY; ++i) {
            dispB[i] = i;
            sizeB[i] = 1;
        }


        MPI_Type_vector(highPart, lenPart, N3, MPI_DOUBLE, &types[0]);
        MPI_Type_struct(2, bLen, disp, types, &typeC);
        MPI_Type_commit(&typeC);

        dispC = new int[sizeX * sizeY];
        sizeC = new int[sizeX * sizeY];
        for(int i = 0; i < sizeX; ++i) {
            for(int j = 0; j < sizeY; ++j) {
                dispC[i * sizeY + j] = (i * sizeY * highPart + j);//считаем смещение для каждого квадратика матрицы Ц
                sizeC[i * sizeY + j] = 1;
            }
        }
    }

    if(coords[1] == 0) {
        MPI_Scatter(A, highPart * N2, MPI_DOUBLE, partA,  highPart * N2, MPI_DOUBLE, 0,
                  comm1D[0]);
    }

//    for(int i = 0; i < highPart && rank == 1; ++i) {
//        for(int j = 0; j < N2; ++j) {
//            printf(" %3.1f", partA[N2*i + j]);
//        }
//        cout << endl;
//    }

    if(coords[0] == 0) {
        MPI_Scatterv(B, sizeB, dispB, typeB, partB, N2 * lenPart, MPI_DOUBLE, 0,
                   comm1D[1]);
    }

    MPI_Bcast(partA, highPart * N2, MPI_DOUBLE, 0, comm1D[1]);
    MPI_Bcast(partB,  N2 * highPart, MPI_DOUBLE, 0, comm1D[0]);

    //основной цикл перемножения
    for(int i = 0; i < highPart; i++) {
        for(int j = 0; j < lenPart; j++) {
            partC[lenPart * i + j] = 0.0;
            for(int k = 0; k < N2; k++) {
                partC[lenPart*i + j] = partC[lenPart*i + j] +
                        partA[N2*i + j] *  partB[lenPart*i + j];
            }
        }
    }

    //адрес что передавать, сколько такого передать, какой у этого тип, куда передать,
    //sizeC - число элементов, которое должно быть получено от i-го процесса
    //смещение i-го блока данных, отн-о начала С, тип данных в котором получаем(не тот, в котором отдаём)
    //в какой процесс, в какой коммутатор
    MPI_Gatherv(partC, lenPart * highPart, MPI_DOUBLE, C, sizeC, dispC, typeC, 0, comm2D);

    delete[] partA;
    delete[] partB;
    delete[] partC;

    MPI_Comm_free(&comm2D);
    for(int i = 0; i < NUM_DIMS; i++) {
        MPI_Comm_free(&comm1D[i]);
    }

    if(rank == 0) {
        delete[] dispB;
        delete[] sizeB;
        delete[] dispC;
        delete[] sizeC;

        MPI_Type_free(&typeB);
        MPI_Type_free(&typeC);
        MPI_Type_free(&types[0]);
    }

    return;
}
