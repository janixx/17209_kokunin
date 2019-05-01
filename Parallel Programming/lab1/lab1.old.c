#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

//#define FIRST
const int B_VECT = 10; //for vector b sending/recieving
const int X_VECT = 11; //for vector x sending/recieving
const int ONE_DIGIT = 12; //messages with only one element
const int ALL_GOOD = 0;
const int ALL_BAD = 1;
const int N = 10000;
const double tau = 0.01;
const double eps = 10e-5;

void swapf(double **a, double **b) {
	double *tmp = *a;
	*a = *b;
	*b = tmp;
}

void init(int threadCt, int threadRk, double **x, double **b, double **a, int **forThread, int *startLine) {
	*forThread = (int*)malloc(threadCt * sizeof(int));
	//������� - ������ �������������� �/� �������� ������������ - ��������� ������ �������� ������
	//�� ���� ������ ����� ��� �������� �������� (���� �������������)
	for (int i = 0; i < threadCt; i++) {
		(*forThread)[i] = i < threadCt - (N % threadCt) ? (N / threadCt) : (N / threadCt + 1);
	}
	for (int i = 0; i < threadRk; i++) {
		*startLine += (*forThread)[i];
	}
#ifdef FIRST
	*x = (double*)calloc(N, sizeof(double));
	*b = (double*)malloc(N * sizeof(double));
	for (int i = 0; i < N; i++) {
		(*b)[i] = N + 1;
	}
#else
	*x = (double*)calloc((N / threadCt + 1), sizeof(double));
	*b = (double*)malloc((*forThread)[threadRk], sizeof(double));
	for (int i = 0; i < (*forThread)[threadRk]; i++) {
		(*b)[i] = N + 1;
	}
#endif
	*a = (double*)malloc(N * (*forThread)[threadRk] *sizeof(double));
	for (int i = 0; i < (*forThread)[threadRk]; i++) {
		for (int j = 0; j < N; j++) {
			(*a)[i * N + j] = (*startLine + i == j) ? 2 : 1;
		}
	}
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

	MPI_Comm_size(MPI_COMM_WORLD, &threadCt);// ��������� ����� ���������
	MPI_Comm_rank(MPI_COMM_WORLD, &threadRk);	// ��������� ������ ��������
	//MPI_COMM_WORLD -- ��������� ���� MPI_Comm, ���������� �� ������� ����� "��� ���������"
	init(threadCt, threadRk, &x, &b, &a, &forThread, &startLine);
	printf("    Number %d thread from %d started; lines %d-%d from %d \n",
		threadRk, threadCt, startLine, startLine + forThread[thredRk], threadCt);

	//��� ��������
	A = (double**)malloc(forThread[threadRk] * sizeof(double*));
	for (int i = 0; i < forThread[threadRk]; i++) {
		A[i] = a + i * N;
	}

#ifdef FIRST
	if (threadRk == 0) {
		start = MPI_Wtime();
		for (int i = 0; i < N; i++) {
			bNorm += b[i] * b[i];
		}
		bNorm = sqrt(bNorm);
	}

	int flag = ALL_BAD;
	//������� ������� � ��� ��������� ��������, ����������� ����� �������
	double *xThread = (double*)malloc(forThread[threadRk] * sizeof(double));

	do {
		double threadRet = 0;//����� ���������� ����� (A * x - b)

		//������� x_next  = x - tau * (A * x - b) �� �������
		for (int i = 0; i < forThread[threadRk]; ++i) {
			double sum = 0;
			//A[i] * x
			for (int j = 0; j < N; ++j) {
				sum += A[i][j] * x[j];
			}
			//A[i] * x - b[i]
			sum -= b[i];
			//x_next[i] = x[i] - tau * (A[i] * x - b[i])
			xThread[i] = x[i + startLine] - sum * tau;
			//����� ������� ����� (A * x - b)
			threadRet += sum * sum;
		}

		//���������� ����� ������ 0
		if (threadRk != 0) {
			MPI_Send(xThread, forThread[threadRk], MPI_DOUBLE, 0, X_VECT, MPI_COMM_WORLD); //���������� ������-�������
			MPI_Send(&thread_ret, 1, MPI_DOUBLE, 0, ONE_DIGIT, MPI_COMM_WORLD); //��������� ����� ���������
			//��������!!!
		}
		else {
			//��������� ���������� � ������-x
			for (int i = startLine; i < startLine + forThread[threadRk]; i++) {
				x[i] = xThread[i - startLine];
			}

			//�������� ���������� ���������� � �������
			double ret = threadRet;
			for (int i = 1, currentLine = forThread[threadRk]; i < threadCt; i++) {
				MPI_Status status;//����� ��-�� ����-�, �����-� �����-�, ��� ������
				//�������� ������-������� � ��������� � ������ ����� ������-�
				//MPI_COMM_WORLD -- ������� ����� �� �����-� (�� ����������)
				MPI_Recv(&x[currentLine], forThread[i], MPI_DOUBLE, i, X_VECT, MPI_COMM_WORLD, &status);
				currentLine += forThread[i];

				double tmp;
				MPI_Recv(&tmp, 1, MPI_DOUBLE, i, ONE_DIGIT, MPI_COMM_WORLD, &status); //�������� ��������� �����
				ret += tmp;
			}
			ret = sqrt(ret);	//����� Ax - b

			flag = (ret / bNorm <= eps) ? ALL_GOOD : ALL_BAD;
		}

		//��������� ������ ����� � ������� x
		MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
		//int MPI_Bcast( void *buf, int count, MPI_Datatype type, int source, MPI_Comm comm);
		MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	} while (flag == ALL_BAD);

	if (threadRank == 0) {
		double finish = MPI_Wtime();
		printf("Threads: %d, time: %lf. \n", threadCount, finish - start);

		//��������� �����
		int answer = ALL_GOOD;
		for (int i = 0; i < N; ++i) {
			if (fabs(fabs(x[i]) - 1) >= eps) {
				answer = ALL_BAD;
				break;
			}
		}
		if (answer == ALL_GOOD) {
			printf("All good, answer is correct :)");
		}
		else {
			printf("Answer isn't correct :O");
		}
	}

	free(xThread);
	free(x);
	free(b);
	free(A);
	free(forThread);

#else 
	if (threadRk != 0) {
		for (int i = 0; i < forThread[threadRk]; i++) {
			bNorm += b[i] * b[i];
		}
		MPI_Send(&bNorm, 1, MPI_DOUBLE, 0, B_VECT, MPI_COMM_WORLD);
	}
	else {
		start = MPI_Wtime();
		for (int i = 0; i < forThread[threadRk]; i++) {
			bNorm += b[i] * b[i];
		}
		for (int i = 0; i < threadCt; i++) {
			double tmp = 0;
			MPI_Status status;//��������� - ����� ��-�� ����-�, �����-� �����-�, ��� ������
				//�������� ������-������� � ��������� � ������ ����� ������-�
				//MPI_COMM_WORLD -- ������� ����� �� �����-� (�� ����������)
			//����, ������� �����, ���, �� ����, �������������?, �������, ������ ����������
			MPI_Recv(&tmp, 1, MPI_DOUBLE, i, B_VECT, MPI_COMM_WORLD, &status);
			bNorm += tmp;
		}
		bNorm = sqrt(bNorm);
	}

	int flag = ALL_BAD,
		next = (threadRk + 1) % threadCt,
		prev = (threadCt + threadRk - 1) % threadCt,
		xSize = (N / threadCount + 1);
	//���� ������ ����� �����
	double *tmpSumAx = (double*)malloc(forThread[threadRk] * sizeof(double);
	double *tmpX = (double*)malloc(xSize * sizeof(double));
	do {
		for (int i = 0; i < forThread[threadRk]; i++) {
			tmpSumAx[i] = 0;
		}
		//������ ���������� � ������� ���������� ��� ������� ������� �
		int coords = startLine;
		//�������� ���� ������ �, ���������� ������ ��� �������
		for (int i = threadRk; i < threadCt + threadRk; i++) {
			//�������� ������ ����� �������, ������������� ������ �������� 
			for (int j = 0; j < forThread[threadRk]; j++) {
				for (int k = coords; k < coords + forThread[i]; k++) {
					tmpSumAx[j] += A[j][k] * x[k - coords];
				}
			}

			MPI_Status status;
			MPI_Sendrecv(x, xSize, MPI_DOUBLE, prev, X_VECT,
				tmpX, xSize, MPI_DOUBLE, next, X_VECT,
				MPI_COMM_WORLD, &status);
			
			swapf(&x, &tmpX);
			//�� ��������� ������� � ������� ������� ��
			coords = (coords + forThread[i]) % N;
		}

		//������ ��� �������� ����� (Ax - b) / b < eps
		double threadRet = 0;

		for (int i = 0; i < forThread[threadRk]; i++) {
			tmpSumAx[i] -= b[i];
			x[i] = x[i] - tau * tmpSumAx[i];//NENENNENENENENENE
			threadRet += tmpSumAx[i] * tmpSumAx[i];
		}
		
		if (threadRk != 0) {
			MPI_Send(&threadRet, 1, MPI_DOUBLE, 0, ONE_DIGIT, MPI_COMM_WORLD);
		}
		else {
			double finalRet = threadRet, tmp = 0.0;
			for (int i = 1; i < threadCt; i++) {
				MPI_Status status;
				MPI_Recv(&tmp, 1, MPI_DOUBLE, i, ONE_DIGIT, MPI_COMM_WORLD, &status);
				finalRet += tmp;
			}
			finalRet = sqrt(finalRet);
			flag = (finalRet / bNorm <= eps) ? ALL_GOOD : ALL_BAD;
		}
		MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
	} while (flag == ALL_BAD);

	if (threadRk != 0) {
		MPI_Send(x, forThread[threadRk], MPI_DOUBLE, 0, X_VECT, MPI_COMM_WORLD);
	} else {
		double *allX = malloc(N * sizeof(double));
		for (int i - 0; i < 0; i++) {
			allX[i] = x[i];
		}
		int line = forThread[threadRk];
		for (int i = 1; i < threadCt; i++) {
			MPI_Status status;
			MPI_Recv(allX + line, forThread[i], MPI_DOUBLE, i, X_VECT, MPI_COMM_WORLD, &status);
			line += forThread[i];
		}
		double finish = MPI_Wtime();
		printf("Threads: %d, time: %lf. \n", threadCount, finish - start);
		//��������� �����
		int ret = ALL_GOOD;
		for (int i = 0; i < N; ++i) {
			if (fabs(fabs(allX[i]) - 1) >= eps) {
				ret = ALL_BAD;
				break;
			}
		}
		free(allX);
		free(tmpX);
		free(tmpSumAx);
		if (ret == ALL_GOOD) {
			printf("All good, answer is correct :)\n");
		}
		else {
			printf("Answer isn't correct :O\n");
		}
	}
	free(x);
	free(b);
	free(a);
	free(A);
	free(forThread);

#endif

	MPI_Finalize();
	return 0;
}


//int main(int argc, char *argv[]) {
//	MPI_Init(&argc, &argv);		// ������������� MPI 
//								//����������� ���� ���, ���� ��� ����������� -- �������
//	int threadRank = 0,			//����� ������
//		threadCount = 0,		//���������� ���������
//		start_line = 0;			//��������� ������ ��� ������ ��������
//	double norm_b = 0.0, start = 0.0;
//
//	int *forThread = nullptr;		//����� ������� �� ���� ������� (������)
//	double	*b = nullptr,
//			*x = nullptr,
//			*A = nullptr;
//
//	MPI_Comm_size(MPI_COMM_WORLD, &threadCount);// ��������� ����� ���������
//	MPI_Comm_rank(MPI_COMM_WORLD, &threadRank);	// ��������� ������ ��������
//	//MPI_COMM_WORLD -- ��������� ���� MPI_Comm, ���������� �� ������� ����� "��� ���������"
//
//	init(threadCount, threadRank, &x, &b, &A, &forThread, &start_line);//��������� �������
//
//	printf("Number %d from %d; LINES: %d-%d (%d)\n", threadRank, threadCount, start_line,
//		start_line + forThread[threadRank], forThread[threadRank]);
//
//	//������� ����� ������� b � �������� �����
//
//	if (threadRank == 0) {
//		start = MPI_Wtime();//����� ��������� � ������ ������-�� �������
//
//		for (int i = 0; i < N; ++i) {
//			norm_b += b[i] * b[i];
//		}
//		norm_b = sqrt(norm_b);
//	}
//
//	bool flag = true;
//	//������� ������� � ��� ��������� ��������, ����������� ����� �������
//	double *thread_x = (double*)malloc(forThread[threadRank] * sizeof(double));
//
//	do {
//		double thread_ret = 0;//����� ���������� ����� (A * x - b)
//
//		//������� x_next  = x - tau * (A * x - b) �� �������
//		for (int i = 0; i < forThread[threadRank]; ++i) {
//			double sum = 0;
//			//A[i] * x
//			for (int j = 0; j < N; ++j) {
//				sum += A[i * N + j] * x[j];
//			}
//			//A[i] * x - b[i]
//			sum -= b[i];
//			//x_next[i] = x[i] - tau * (A[i] * x - b[i])
//			thread_x[i] = x[i + start_line] - sum * tau;
//			//����� ������� ����� (A * x - b)
//			thread_ret += sum * sum;
//		}
//
//		//���������� ����� ������ 0
//		if (threadRank != 0) {
//			MPI_Send(thread_x, forThread[threadRank], MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); //���������� ������-�������
//			MPI_Send(&thread_ret, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD); //��������� ����� ���������
//			//��������!!!
//		} else {
//			//��������� ���������� � ������-x
//			for (int i = start_line; i < start_line + forThread[threadRank]; ++i) {
//				x[i] = thread_x[i - start_line];
//			}
//
//			//�������� ���������� ���������� � �������
//			double ret = thread_ret;
//			for (int i = 1, currentLine = forThread[threadRank]; i < threadCount; ++i) {
//				MPI_Status status;//����� ��-�� ����-�, �����-� �����-�, ��� ������
//				//�������� ������-������� � ��������� � ������ ����� ������-�
//				//MPI_COMM_WORLD -- ������� ����� �� �����-� (�� ����������)
//				MPI_Recv(&x[currentLine], forThread[i], MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
//				currentLine += forThread[i];
//
//				double tmp;
//				MPI_Recv(&tmp, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status); //�������� ��������� �����
//				ret += tmp;
//			}
//			ret = sqrt(ret);	//����� Ax - b
//
//			flag = (ret / normB >= eps);
//		}
//
//		//��������� ������ ����� � ������� x
//		MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
//		//int MPI_Bcast( void *buf, int count, MPI_Datatype type, int source, MPI_Comm comm);
//		MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//	} while (flag);
//
//	if (threadRank == 0) {
//		double finish = MPI_Wtime();
//		printf("Threads: %d, time: %lf. \n", threadCount, finish - start);
//
//		//��������� �����
//		bool answer = true;
//		for (int i = 0; i < N; ++i) {
//			if (fabs(fabs(x[i]) - 1) >= eps) {
//				answer = false;
//				break;
//			}
//		}
//		if (answer)
//			printf("All good, answer is correct :)");
//		else 
//			printf("Answer isn't correct :O");
//	}