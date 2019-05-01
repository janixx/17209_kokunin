#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define N 10000
#define tau 10e-6
#define eps 10e-5

#define ALL_GOOD 0
#define ALL_BAD 1

//void init(int **perThreads, int *startLine, double **matrix, double **b, double **x, int count, int rank);
void init(int **perThreads, int *startLine, double **matrix, double **b, double **x, int count, int rank) {
    *perThreads = (int*)malloc(count * sizeof(int));
    for(int i = 0, tmp = count - (N % count); i < count; ++i) {
        (*perThreads)[i] = i < tmp ? (N / count) : (N / count + 1);
        if(i < rank) {
            *startLine += (*perThreads)[i];
        }
    }

    //Генерируем данные для данного потока. В реальной задаче лучше сделать чтение из файлы и т.п.
    *matrix = (double*)malloc( (*perThreads)[rank] * N * sizeof(double));
    
    for(int i = 0; i < (*perThreads)[rank]; ++i) {
        for(int j = 0; j < N; ++j) {
            (*matrix)[i * N + j] = ((*startLine) + i) == j ? 2 : 1;
        }
    }

    *b = (double*)malloc( (*perThreads)[rank] * sizeof(double));
    for(int i = 0; i < (*perThreads)[rank]; ++i) {
        (*b)[i] = N + 1;
    }

    *x = (double*)calloc(N / count + 1, sizeof(double));
}

double normVector(const double * vector, int length) {
    double answer = 0;
    for(int i = 0; i < length; ++i) {
        answer += vector[i] * vector[i];
    }
    return answer;
}

//void multiplyOnConst(double * vector, int length, double c, double * answer);

void nullifyVector(double * vector, int length) {
    for(int i = 0; i < length; ++i) {
        vector[i] = 0;
    }
}

void swapf(double **a, double **b) {
	double *tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(int argc, char ** argv) {
    MPI_Init(&argc, &argv);
    
    int rank = 0;
    int count = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &count);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int startLine = 0;
    int *perThreads = 0;
    double *matrix = 0;
    double *b = 0;
    double *x = 0;
    init(&perThreads, &startLine, &matrix, &b, &x, count, rank);

    double *tmpSum = (double*)malloc(perThreads[rank] * sizeof(double) ); //сумма строк
    double *tmpX = (double*)calloc((N / count + 1), sizeof(double) );

    printf("\tNumber %d thread from %d started; lines %d-%d (%d) \n", rank, count, startLine,
           startLine + perThreads[rank], perThreads[rank]);

    //Считаем норму вектора b и засекаем время
    double start = 0;
    double normB = 0;
    if(rank == 0) {
        start = MPI_Wtime();
        
        normB = normVector(b, perThreads[rank]);
        
        for(int i = 1; i < count; ++i) {
            double tmp;
            MPI_Status status;
            MPI_Recv(&tmp, 1, MPI_DOUBLE, i, 4, MPI_COMM_WORLD, &status); //получаем столбец
            normB += tmp;
        }
        normB = sqrt(normB);
    } else {
        normB = normVector(b, perThreads[rank]);

        MPI_Send(&normB, 1, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD); //отправляем b
    }

    int flag = ALL_BAD;
    while(flag == ALL_BAD) {

        nullifyVector(tmpSum, perThreads[rank]);

        //цикл по вектору x
        for(int i = rank, currentCrds = startLine; i < count + rank; ++i) {
            //цикл по строкам
            for(int j = 0; j < perThreads[rank]; ++j) {
                //цикл по координатам
                for(int k = currentCrds, c = currentCrds + perThreads[i % count]; k < c; ++k) {
                    tmpSum[j] += matrix[j * N + k] * x[k - currentCrds];
                }
            }

            MPI_Status status;

            MPI_Sendrecv(x, N / count + 1, MPI_DOUBLE, (rank - 1 + count) % count, 0,
            tmpX, N / count + 1, MPI_DOUBLE, (rank + 1) % count, 0, MPI_COMM_WORLD, &status);

            swapf(&x, &tmpX);
            currentCrds = (currentCrds + perThreads[i % count]) % N;
        }

        double threadAnswer = 0;

        for(int i = 0; i < perThreads[rank]; ++i) {
            tmpSum[i] -= b[i];

            double copyX = x[0];

            x[i] = x[i] - tmpSum[i] * tau;
            threadAnswer += tmpSum[i] * tmpSum[i];
        }

        //Отправляем ответ 0 потоку
        if(rank == 0) {
            double sum = threadAnswer;
            for(int i  = 1; i < count; ++i) {
                MPI_Status status;
                double tmp;
                MPI_Recv(&tmp, 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &status); //получаем частичную сумму

                sum += tmp;

            }

            sum = sqrt(sum);

            flag = sum / normB >= eps;
        } else {

            MPI_Send(&threadAnswer, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD); //частичную сумму координат

        }
        //Обновляем данные флага
        MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if(rank == 0) {
        double * fullX = (double*)malloc(N * sizeof(double));
        for(int i = 0; i < perThreads[rank]; ++i) {
            fullX[i] = x[i];
        }

        for(int i = 1, currentLine = perThreads[rank]; i < count; ++i) {
            MPI_Status status;
            MPI_Recv(&fullX[currentLine], perThreads[i], MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status); //получаем столбец
            currentLine += perThreads[i];
        }

        double finish = MPI_Wtime();
        printf("\tThreads: %d, time: %3.5lf \n", count, finish - start);

        //проверяем ответ
        int flag = ALL_GOOD;
        for(int i = 0; i < N; ++i) {
            if(fabs(fabs(fullX[i]) - 1) >= eps) {
                flag = ALL_BAD;
                break;
            }
        }
        if (flag == ALL_GOOD) {
            printf("\n\tAnswer is correct :) \n");
        } else {
            printf("\n\tAnswer isn't correct :( \n");
        }

        free(fullX);
        
    } else {
        
        MPI_Send(x, perThreads[rank], MPI_DOUBLE, 0, 1, MPI_COMM_WORLD); //отправляем столбец значений
        
    }

    free(tmpX);
    free(x);
    free(b);
    free(matrix);
    free(perThreads);

    MPI_Finalize();
    return 0;
}


