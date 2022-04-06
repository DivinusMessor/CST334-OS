#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define N 1024	   //# rows of matrix A
#define M 1024	   //# columns  matrix A & # rows matrix B
#define L 1024	   //# colummns matrix B
#define NTHREADS N //# threads
pthread_t threads[NTHREADS];

double matrixA[N][M]; // initialize matrix A
double matrixB[M][L]; // initialize matrix B
double matrixC[N][L]; // initialize result matrix C

void *math(void *arg)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < L; j++)
		{
			double temp = 0;
			for (int k = 0; k < M; k++)
			{
				temp += matrixA[i][k] * matrixB[k][j];
			}
			matrixC[i][j] = temp;
		}
	}
}

int main()
{
	srand(time(NULL));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			matrixA[i][j] = rand() % 10;
			matrixB[i][j] = rand() % 10;
		}

	// printf("========Matrix A==========\n");
	// for (int i = 0; i < N; i++)
	// {
	// 	for (int j = 0; j < M; ++j)
	// 	{
	// 		if (j == (M - 1))
	// 		{
	// 			printf(" %g  ", matrixA[i][j]);
	// 			printf("\n");
	// 		}
	// 		else
	// 		{
	// 			printf(" %g ", matrixA[i][j]);
	// 		}
	// 	}
	// }
	// printf("=========Matrix B==========\n");
	// for (int i = 0; i < M; i++)
	// {
	// 	for (int j = 0; j < L; ++j)
	// 	{
	// 		if (j == (L - 1))
	// 		{
	// 			printf(" %g  ", matrixB[i][j]);
	// 			printf("\n");
	// 		}
	// 		else
	// 		{
	// 			printf(" %g ", matrixB[i][j]);
	// 		}
	// 	}
	// }
	// Make threads
	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_create(&threads[i], NULL, math, (void *)i);
	}
	// join threads
	for (int i = 0; i < NTHREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}
	printf("========Matrix C=========\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < L; j++)
		{
			if (j == (L - 1))
			{
				printf(" %g ", matrixC[i][j]);
				printf("\n");
			}
			else
			{
				printf(" %g ", matrixC[i][j]);
			}
		}
	}
}