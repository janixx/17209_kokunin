#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define FIRST

const int N = 10000;
const double tau = 0.01;
const double eps = 10e-5;

void init(int threadCount, int threadRank, double **x, double **b, double **A, int **per_threads, int *start_line) {
	*per_threads = (int*)malloc(threadCount * sizeof(int));
	int tmp = threadCount - (N % threadCount);
	//������� - ������ �������������� �/� �������� ������������ - ��������� ������ �������� ������
	//�� ���� ������ ����� ��� �������� �������� (���� �������������)
	for (int i = 0; i < threadCount; ++i) {
		(*per_threads)[i] = i < tmp ? (N / threadCount) : (N / threadCount + 1);
		*start_line += i < threadRank ? (*per_threads)[i] : 0;
	}

	*x = (double*)calloc(N, sizeof(double));

	*b = (double*)malloc((*per_threads)[threadRank] * sizeof(double));
	for (int i = 0; i < (*per_threads)[threadRank]; ++i) {
		(*b)[i] = N + 1;
	}

	*A = (double*)malloc((*per_threads)[threadRank] * N * sizeof(double));
	for (int i = 0; i < (*per_threads)[threadRank]; ++i) {
		for (int j = 0; j < N; ++j) {
			(*A)[i * N + j] = ((*start_line) + i) == j ? 2 : 1;
		}
	}
	////���������� ������ ��� ������� ������. � �������� ������ ����� ������� ������ �� ����� � �.�.
	//*matrix = new double[(*perThreads)[threadRank] * N];
	//for (int i = 0; i < (*perThreads)[threadRank]; ++i) {
	//	for (int j = 0; j < N; ++j) {
	//		(*matrix)[i * N + j] = ((*startLine) + i) == j ? 2 : 1;
	//	}
	//}

	//*b = new double[(*perThreads)[threadRank]];
	//for (int i = 0; i < (*perThreads)[threadRank]; ++i) {
	//	(*b)[i] = N + 1;
	//}

	//*x = new double[(*perThreads)[threadRank]]();
}

#ifdef FIRST

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);		// ������������� MPI 
								//����������� ���� ���, ���� ��� ����������� -- �������
	int threadRank = 0,			//����� ������
		threadCount = 0,		//���������� ���������
		start_line = 0;			//��������� ������ ��� ������ ��������
	double norm_b = 0.0, start = 0.0;

	int *per_thread = nullptr;		//����� ������� �� ���� ������� (������)
	double	*b = nullptr,
			*x = nullptr,
			*A = nullptr;

	MPI_Comm_size(MPI_COMM_WORLD, &threadCount);// ��������� ����� ���������
	MPI_Comm_rank(MPI_COMM_WORLD, &threadRank);	// ��������� ������ ��������

	init(threadCount, threadRank, &x, &b, &A, &per_thread, &start_line);//��������� �������

	printf("Number %d from %d; LINES: %d-%d (%d)\n", threadRank, threadCount, start_line,
		start_line + per_thread[threadRank], per_thread[threadRank]);

	//������� ����� ������� b � �������� �����

	if (threadRank == 0) {
		start = MPI_Wtime();//����� ��������� � ������ ������-�� �������

		for (int i = 0; i < N; ++i) {
			norm_b += b[i] * b[i];
		}
		norm_b = sqrt(norm_b);
	}

	bool flag = true;
	//������� ������� � ��� ��������� ��������, ����������� ����� �������
	double *thread_x = (double*)malloc(per_thread[threadRank] * sizeof(double));

	do {
		double thread_ret = 0;//����� ���������� ����� (A * x - b)

		//������� x_next  = x - tau * (A * x - b) �� �������
		for (int i = 0; i < per_thread[threadRank]; ++i) {
			double sum = 0;
			//A[i] * x
			for (int j = 0; j < N; ++j) {
				sum += A[i * N + j] * x[j];
			}
			//A[i] * x - b[i]
			sum -= b[i];
			//x_next[i] = x[i] - tau * (A[i] * x - b[i])
			thread_x[i] = x[i + start_line] - sum * tau;
			//����� ������� ����� (A * x - b)
			thread_ret += sum * sum;
		}

		//���������� ����� ������ 0
		if (threadRank != 0) {
			MPI_Send(thread_x, per_thread[threadRank], MPI_DOUBLE, 0, 0, MPI_COMM_WORLD); //���������� ������-�������
			MPI_Send(&thread_ret, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD); //��������� ����� ���������
			//��������!!!
		} else {
			//��������� ���������� � ������-x
			for (int i = start_line; i < start_line + per_thread[threadRank]; ++i) {
				x[i] = thread_x[i - start_line];
			}

			//�������� ���������� ���������� � �������
			double ret = thread_ret;
			for (int i = 1, currentLine = per_thread[threadRank]; i < threadCount; ++i) {
				MPI_Status status;
				//�������� ������-������� � ��������� � ������ ����� ������-�
				MPI_Recv(&x[currentLine], per_thread[i], MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
				currentLine += per_thread[i];

				double tmp;
				MPI_Recv(&tmp, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status); //�������� ��������� �����
				ret += tmp;
			}
			ret = sqrt(ret);	//����� Ax - b

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

	free(thread_x);
	free(x);
	free(b);
	free(A);
	free(per_thread);

	MPI_Finalize();
	return 0;
}

#else 

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	int threadRank = 0;
	int threadCount = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &threadCount);
	MPI_Comm_rank(MPI_COMM_WORLD, &threadRank);

	int startLine = 0;
	int *perThreads = 0;
	double *matrix = 0;
	double *b = 0;
	double *x = 0;

	init(&perThreads, &startLine, &matrix, &b, &x, threadCount, threadRank);

	double *tmpSum = new double[perThreads[threadRank]]; //����� �����
	double *tmpX = new double[N / threadCount + 1]();

	printf("I'm %d from %d and my lines: %d-%d (%d)\n", threadRank, threadCount, startLine,
		startLine + perThreads[threadRank], perThreads[threadRank]);

	//������� ����� ������� b � �������� �����
	double start = 0;
	double normB = 0;
	if (threadRank != 0) {
		for (int i = 0; i < perThreads[threadRank]; ++i) {
			normB += b[i] * b[i];
		}
		MPI_Send(&normB, 1, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD); //���������� b
	}
	else {
		start = MPI_Wtime();

		for (int i = 0; i < perThreads[threadRank]; ++i) {
			normB += b[i] * b[i];
		}

		for (int i = 1; i < threadCount; ++i) {
			double tmp;
			MPI_Status status;
			MPI_Recv(&tmp, 1, MPI_DOUBLE, i, 4, MPI_COMM_WORLD, &status); //�������� �������
			normB += tmp;
		}
		normB = sqrt(normB);
	}

	int flag = 1;
	while (flag) {

		for (int i = 0; i < perThreads[threadRank]; ++i) {
			tmpSum[i] = 0;
		}

		//���� �� ������� x
		for (int i = 0, currentCrds = startLine; i < threadCount; ++i) {
			//���� �� �������
			for (int j = 0; j < perThreads[threadRank]; ++j) {
				//���� �� �����������
				for (int k = currentCrds, c = currentCrds + perThreads[i]; k < c; ++k) {
					tmpSum[j] += matrix[j * N + k] * x[k - currentCrds];
				}
			}

			MPI_Status status;

			MPI_Sendrecv(x, N / threadCount + 1, MPI_DOUBLE, (threadRank - 1 + threadCount) % threadCount, 0,
				tmpX, N / threadCount + 1, MPI_DOUBLE, (threadRank + 1) % threadCount, 0, MPI_COMM_WORLD, &status);

			std::swap(x, tmpX);
			currentCrds = (currentCrds + perThreads[i]) % N;
		}

		double threadAnswer = 0;

		for (int i = 0; i < perThreads[threadRank]; ++i) {
			tmpSum[i] -= b[i];

			double copyX = x[0];

			x[i] = x[i] - tmpSum[i] * t;
			threadAnswer += tmpSum[i] * tmpSum[i];
		}

		//���������� ����� 0 ������
		if (threadRank != 0) {

			MPI_Send(&threadAnswer, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD); //��������� ����� ���������

			//�������� ������ � ������ 0
		}
		else {
			//�������� ���������� ���������� � �������
			double sum = threadAnswer;
			for (int i = 1; i < threadCount; ++i) {
				MPI_Status status;
				double tmp;
				MPI_Recv(&tmp, 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &status); //�������� ��������� �����

				sum += tmp;

			}


			sum = sqrt(sum);

			flag = sum / normB >= eps;
		}
		//��������� ������ �����
		MPI_Bcast(&flag, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}

	if (threadRank != 0) {
		MPI_Send(x, perThreads[threadRank], MPI_DOUBLE, 0, 1, MPI_COMM_WORLD); //���������� ������� ��������
	}
	else {
		double *fullX = new double[N];
		for (int i = 0; i < perThreads[threadRank]; ++i) {
			fullX[i] = x[i];
		}

		for (int i = 1, currentLine = perThreads[threadRank]; i < threadCount; ++i) {
			MPI_Status status;
			MPI_Recv(&fullX[currentLine], perThreads[i], MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &status); //�������� �������
			currentLine += perThreads[i];
		}

		double finish = MPI_Wtime();
		std::cout << "Threads: " << threadCount << ", time: " << (finish - start) << std::endl;

		//��������� �����
		bool correctAnswer = true;
		for (int i = 0; i < N; ++i) {
			//std::cout << fullX[i] << " ";
			if (fabs(fabs(fullX[i]) - 1) >= eps) {
				correctAnswer = false;
				break;
			}
		}
		std::cout << "Answer correct: " << correctAnswer << std::endl;

		delete[] fullX;
	}

	delete[] tmpX;
	delete[] x;
	delete[] b;
	delete[] matrix;
	delete[] perThreads;

	MPI_Finalize();
	return 0;
}

#endif