#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

const int N = 10000;
const double eps = 10e-5;
const double tau = 0.00001;

const int ALL_BAD = 0;
const int ALL_GOOD = 1;

int main(int argc, char *argv[]) {
	double *x = (double*)calloc(N, sizeof(double));
	double *b = (double*)malloc(N * sizeof(double));
	double *a = (double*)malloc(N * N * sizeof(double));
	double **A = (double**)malloc(N * sizeof(double));
	double *tmpX = (double*)malloc(N * sizeof(double));
	for (int i = 0; i < N; ++i) {
		A[i] = a + N * i;
	}
	//#pragma omp parallel for
	//printf("I'm in the begin of main() function \n");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			A[i][j] = ((i == j) ? 2.0 : 1.0);
		}
	}
	//#pragma omp parallel for
	for (int i = 0; i < N; ++i) {
		b[i] = N + 1;
	}
	double bNorm = 0.0;
	for (int i = 0; i < N; i++) {
		bNorm += b[i] * b[i];
	}
	struct timeval c0;
	struct timeval c1;
	//printf("Now I will call time function \n");
	gettimeofday(&c0, 0);
	bNorm = sqrt(bNorm);

	//printf("I'm here \n");
	double axNorm = 0.0, sum = 0.0;
	#pragma omp parallel
	{
		int rank, size;
		rank = omp_get_thread_num();
		size = omp_get_num_threads();
		int rowsForProcess = N / size;
		int currentRows = rowsForProcess * rank;

		for (int flag = ALL_BAD; flag != ALL_GOOD;) {
			axNorm = 0.0;

			for (int i = currentRows; i < currentRows + rowsForProcess; ++i) {
				sum = 0.0;
				for (int j = 0; j < N; ++j) {
					sum += A[i][j] * x[j];
				}
				sum -= b[i];
				axNorm += sum * sum;
				tmpX[i] = x[i] - sum * tau;
			}
			for (int i = currentRows; i < currentRows + rowsForProcess; ++i) {
				x[i] = tmpX[i];
			}
	#pragma omp barrier
			if (rank == 0) {
				//printf(" Norm Ax is %10.8lf \n", axNorm);
				axNorm = sqrt(axNorm);
                printf(" Norm Ax is %10.8lf \n", axNorm);
				if (axNorm / bNorm <= eps) {
					flag = ALL_GOOD;
				}
			}
    #pragma omp barrier
		}
	}
	gettimeofday(&c1, 0);
	printf("my time is %d\n", (int)((c1.tv_sec - c0.tv_sec) * 1000000 + c1.tv_usec - c0.tv_usec));

	int ret = ALL_GOOD;
	for (int i = 0; i < N; ++i) {
		//printf("x[%d] = %9.7lf \n", i, x[i]);
		if (fabs(fabs(x[i]) - 1) >= eps) {
			ret = ALL_BAD;
			break;
		}
	}

	//printf("x[10] = %9.7lf \n", x[10]);
	if (ret == ALL_GOOD) {
		printf("All good, answer is correct :)\n");
	}
	else {
		printf("Answer isn't correct :O\n");
	}
	free(A);
	free(a);
	free(b);
	free(tmpX);
	free(x);
}

