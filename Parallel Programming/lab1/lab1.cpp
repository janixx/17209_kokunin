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

	MPI_Init(&argc, &argv);		// ������������� MPI 
								//����������� ���� ���, ���� ��� ����������� �������
	int threadRank = 0;			//����� ������
	int threadCount = 0;		//���������� ���������
	int startLine = 0;			//��������� ������ ��� ������ ��������
	int *perThreads = 0;		//����� ������� �� ���� ������� (������)
	double	*b = nullptr,
			*x = nullptr,
			*matrix = nullptr;
	double norm_b = 0.0, start = 0.0;

	MPI_Comm_size(MPI_COMM_WORLD, &threadCount);// ��������� ����� ���������
	MPI_Comm_rank(MPI_COMM_WORLD, &threadRank);	// ��������� ������ ��������

	init(&perThreads, &startLine, &matrix, &b, &x, threadCount, threadRank);//��������� �������

	printf("Number %d from %d; LINES: %d-%d (%d)\n", threadRank, threadCount, startLine,
		startLine + perThreads[threadRank], perThreads[threadRank]);

	//������� ����� ������� b � �������� �����

	if (threadRank == 0) {
		start = MPI_Wtime();//����� ��������� � ������ ������-�� �������

		for (int i = 0; i < N; ++i) {
			norm_b += b[i] * b[i];
		}
		norm_b = sqrt(norm_b);
	}

	bool flag = true;
	double *thread_x = new double[perThreads[threadRank]];//������� �������-������, ����������� ����� �������
	do {
		double thread_ret = 0;

		//���� �� �������
		for (int i = 0; i < perThreads[threadRank]; ++i) {
			double sum = 0;
			//���� �� �������� A[i] * x
			for (int j = 0; j < N; ++j) {
				sum += matrix[i * N + j] * x[j];
			}
			sum -= b[i]; //A[i] * x - b
			thread_x[i] = x[i + startLine] - sum * t; //��������� ����������, ������� ���������
			thread_ret += sum * sum;
		}

		//���������� ����� ������ 0
		if (threadRank != 0) {
			MPI_Send(thread_x, perThreads[threadRank], MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); //���������� ������-�������
			MPI_Send(&thread_ret, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD); //��������� ����� ���������
			//��������!!!
		} else {
			//��������� ���������� � ������-x
			for (int i = startLine, c = startLine + perThreads[threadRank]; i < c; ++i) {
				x[i] = thread_x[i - startLine];
			}

			//�������� ���������� ���������� � �������
			double ret = thread_ret;
			for (int i = 1, currentLine = perThreads[threadRank]; i < threadCount; ++i) {
				MPI_Status status;
				//�������� ������-������� � ��������� � ������ ����� ������-�
				MPI_Recv(&x[currentLine], perThreads[i], MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
				currentLine += perThreads[i];

				double tmp;
				MPI_Recv(&tmp, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status); //�������� ��������� �����
				ret += tmp;
			}
			ret = sqrt(ret);	//

			flag = (ret / normB >= eps);
		}
		//��������� ������ ����� � ������� x
		MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
		//int MPI_Bcast( void *buf, int count, MPI_Datatype type, int source, MPI_Comm comm);
		MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	} while (flag);

	if (threadRank == 0) {
		double finish = MPI_Wtime();
		printf("Threads: %d, time: %lf. \n", threadCount, finish - start);

		//��������� �����
		bool answer = true;
		for (int i = 0; i < N; ++i) {
			//std::cout << x[i] << " ";
			if (fabs(fabs(x[i]) - 1) >= eps) {
				answer = false;
				break;
			}
		}
		if (answer)
			printf("All good, answer is correct :)");
		else 
			printf("Answer isn't correct :O");
	}

	delete[] threadX;
	delete[] x;
	delete[] b;
	delete[] matrix;
	delete[] perThreads;

	MPI_Finalize();
	return 0;
}

void init(int **perThreads, int *startLine, double **matrix, double **b, double **x, int threadCount, int threadRank) {
	*perThreads = new int[threadCount]();
	for (int i = 0, tmp = threadCount - (N % threadCount); i < threadCount; ++i) {
		(*perThreads)[i] = i < tmp ? (N / threadCount) : (N / threadCount + 1);
		if (i < threadRank) {
			*startLine += (*perThreads)[i];
		}
	}

	//���������� ������ ��� ������� ������. � �������� ������ ����� ������� ������ �� ����� � �.�.
	*matrix = new double[(*perThreads)[threadRank] * N];
	for (int i = 0; i < (*perThreads)[threadRank]; ++i) {
		for (int j = 0; j < N; ++j) {
			(*matrix)[i * N + j] = ((*startLine) + i) == j ? 2 : 1;
		}
	}

	*b = new double[(*perThreads)[threadRank]];
	for (int i = 0; i < (*perThreads)[threadRank]; ++i) {
		(*b)[i] = N + 1;
	}

	*x = new double[N]();
}