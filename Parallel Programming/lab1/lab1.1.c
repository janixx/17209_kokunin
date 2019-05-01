
#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

const int B_VECT = 10; //for vector b sending/recieving
const int X_VECT = 11; //for vector x sending/recieving
const int ONE_DIGIT = 12; //messages with only one element
const int ALL_GOOD = 0;
const int ALL_BAD = 1;
const int N = 10000;
const double tau = 10e-6;
const double eps = 10e-5;

void swapf(double **a, double **b) {
	double *tmp = *a;
	*a = *b;
	*b = tmp;
}

void printTenX(double *x, double *tmpX) {
	printf("Ten elements from X: ");
	for (int i = 0; i < 10; i++) {
		printf("%f.2 ", x[i]);
	}
	printf("\n");
	printf("Ten elements from tmpX: ");
	for (int i = 0; i < 10; i++) {
		printf("%f.2 ", tmpX[i]);
	}
	printf("\n");
}

void init(int threadCt, int threadRk, double **x, double **b, double **a, int **forThread, int *startLine) {
	//printf("I'm #%d in the begin of init func \n", threadRk);
	*forThread = (int*)malloc(threadCt * sizeof(int));
	for (int i = 0; i < threadCt; i++) {
		(*forThread)[i] = (i < threadCt - (N % threadCt)) ? (N / threadCt) : (N / threadCt + 1);
	}
	for (int i = 0; i < threadRk; i++) {
		*startLine += (*forThread)[i];
	}

	*x = (double*)calloc(N, sizeof(double));
	
    *b = (double*)malloc(N * sizeof(double));
	for (int i = 0; i < N; i++) {
		(*b)[i] = N + 1;
	}

	*a = (double*)malloc(N * (*forThread)[threadRk] * sizeof(double));
	for (int i = 0; i < (*forThread)[threadRk]; i++) {
		for (int j = 0; j < N; j++) {
			(*a)[i * N + j] = (*startLine + i == j) ? 2 : 1;
		}
	}
	//printf("I'm #%d in the end of init func \n", threadRk);
}

int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int threadRk = 0,
		threadCt = 0,
		startLine = 0,
		*forThread = NULL;
	double bNorm = 0.0,
		start = 0.0,
		*b = NULL,
		*x = NULL,
		*a = NULL,
		**A = NULL;

	MPI_Comm_size(MPI_COMM_WORLD, &threadCt);
	MPI_Comm_rank(MPI_COMM_WORLD, &threadRk);
	init(threadCt, threadRk, &x, &b, &a, &forThread, &startLine);
	printf("\tNumber %d thread from %d started; lines %d-%d (%d) \n",
		threadRk, threadCt, startLine, startLine + forThread[threadRk], forThread[threadRk]);

	A = (double**)malloc(forThread[threadRk] * sizeof(double*));
	for (int i = 0; i < forThread[threadRk]; i++) {
		A[i] = a + i * N;
	}

	if (threadRk == 0) {
		start = MPI_Wtime();
		for (int i = 0; i < N; i++) {
			bNorm += b[i] * b[i];
		}
		bNorm = sqrt(bNorm);
	}

	int flag = ALL_BAD;
	double *xThread = (double*)malloc(forThread[threadRk] * sizeof(double));

	do {
		//printf("I'm #%d in the begin of main cicle \n", threadRk);
		double threadRet = 0;

		for (int i = 0; i < forThread[threadRk]; ++i) {
			double sum = 0;
			for (int j = 0; j < N; ++j) {
				sum += A[i][j] * x[j];
			}
			sum -= b[i];
			xThread[i] = x[i + startLine] - sum * tau;
			threadRet += sum * sum;
		}

		if (threadRk != 0) {
			MPI_Send(xThread, forThread[threadRk], MPI_DOUBLE, 0, X_VECT, MPI_COMM_WORLD);
			MPI_Send(&threadRet, 1, MPI_DOUBLE, 0, ONE_DIGIT, MPI_COMM_WORLD);
		}
		else {
			for (int i = startLine; i < startLine + forThread[threadRk]; i++) {
				x[i] = xThread[i - startLine];
			}

			double ret = threadRet;
			for (int i = 1, currentLine = forThread[threadRk]; i < threadCt; i++) {
				MPI_Status status;
				MPI_Recv(&x[currentLine], forThread[i], MPI_DOUBLE, i, X_VECT, MPI_COMM_WORLD, &status);
				currentLine += forThread[i];

				double tmp;
				MPI_Recv(&tmp, 1, MPI_DOUBLE, i, ONE_DIGIT, MPI_COMM_WORLD, &status); //получаем частичную сумму
				ret += tmp;
			}
			ret = sqrt(ret);	//норма Ax - b

			flag = (ret / bNorm <= eps) ? ALL_GOOD : ALL_BAD;
		}

		MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		//printf("I'm #%d in the end of main cicle \n", threadRk);
	} while (flag == ALL_BAD);

	if (threadRk == 0) {
		//printf("I'm #%d preparing answer \n", threadRk);
		double finish = MPI_Wtime();
		printf("\tThreads: %d, time: %lf. \n", threadCt, finish - start);

		int answer = ALL_GOOD;
		for (int i = 0; i < N; i++) {
			if (fabs(fabs(x[i]) - 1) >= eps) {
				answer = ALL_BAD;
				break;
			}
		}
		if (answer == ALL_GOOD) {
			printf("\n\tAnswer is correct :) \n");
		}
		else {
			printf("\n\tAnswer isn't correct :O \n");
		}
	}

	free(xThread);
	free(x);
	free(b);
	free(A);
	free(a);
	free(forThread);
	MPI_Finalize();
	return 0;
}
