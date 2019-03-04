#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

const int N = 1000;
const double t = 10e-6;
const double E = 10e-5;

void init(int **perThreads, int *startLine, double **matrix, double **b, double **x, int threadCount, int threadRank);

int main(int argc, char *argv[]) {
	//printf("Write matrix rank: ");
	//int N = 5, i = 0, count = 0, number = 0;
	//scanf("%d", &N);
	//printf("\n");

	MPI_Init(&argc, &argv);

	int threadRank = 0;
	int threadCount = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &threadCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &threadRank);

	double	*b = malloc(N * sizeof(double)),
			*x = malloc(N * sizeof(double)),
			*A_str = malloc(N * N * sizeof(double));
	double **A = malloc(N * sizeof(double*));

	for (i = 0; i < N; i++)
		A[i] = A_str + i * N;

	MPI_Init(&argc, &argv); // Инициализация MPI
	MPI_Comm_size(MPI_COMM_WORLD, &count); // Получение числа процессов
	MPI_Comm_rank(MPI_COMM_WORLD, &number); // Получение номера процесса
	
	printf(“Hello from process #%d of %d\n”, count, number);

	MPI_Finalize();
}
