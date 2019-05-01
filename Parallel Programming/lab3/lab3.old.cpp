#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define NUM_DIMS 2
#define P0 2
#define P1 2

#define N1 8
#define N2 8
#define N3 8
#define A((i),(j)) A[N1*(i)+(j)]
#define B(i,j) B[N3*(i)+(j)]
#define C(i,j) C[N3*(i)+(j)]


int main(int argc, char * argv[]) {
    int size, rank;
   
    double *A = new double[N1 * N2];
    double *B = new double[N2 * N3];
    double *C = new double[N1 * N3];

    

    int p[2] = {0, 0};

    
    
    MPI_Init(&argc, &argv);
    MPI_Comm comm;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double *partA, *partB, *partC;
    int lenPart, highPart

void Build_derived_type(INDATA_TYPE* indata,
     MPI-Datatype* message_type_ptr)

{

  int block_lengths[3];

  MPI_Aint displacements[3];

  MPI_Aint addresses[4];

  MPI_Datatype typelist[3];

 

  /* Создает производный тип данных, содержащий

  * два элемента float и один int */

  /* Сначала нужно определить типы элементов */

  typelist[0] = MPI_FLOAT;

  typelist[1] = MPI_FLOAT;

  typelist[2] = MPI_INT;

 

  /* Определить количество элементов каждого типа */

  block_lengths[0] = block_lengths[1] =

     block_lengths[2] = 1;

  

  /* Вычислить смещения элементов 

  * относительно indata */

  MPI_Address(indata, &addresses[0]);

  MPI_Address(&(indata->a), &addresses[1]);

  MPI_Address(&(indata->b), &addresses[2]);

  MPI_Address(&(indata->n), &addresses[3]);

  displacements[0] = addresses[1] - addresses[0];

  displacements[1] = addresses[2] - addresses[0];

  displacements[2] = addresses[3] - addresses[0];

 

  /* Создать производный тип */

  MPI_Type_struct(3, block_lengths, displacements,

     typelist, Message_type_ptr);

 

  /* Зарегистрировать его для использования */

  MPI_Type_commit(message_type_ptr);

} /* Build_derived_type */

 Build_derived_type(indata, &message_type);

  MPI_Bcast(indata, count, message_type, root,

  MPI_COMM_WORLD);


/*MPI_Type_struct(). Синтаксис этой функции таков:
    
    int MPI_Type_Struct(int count,
    int* array_of_block_lengths,
    
    MPI_Aint* array_of_displacements,
    
    MPI_Datatype* array_of_types,
    
    MPI_Datatype* newtype)
*/
