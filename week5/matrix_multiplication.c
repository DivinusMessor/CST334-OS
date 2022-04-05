#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define N 1024
#define M 1024
#define L 1024

double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];

int main()
{

    srand(time(NULL));
    for (int i = 0; j < N; i++)
        for (int j = 0; j < M; j++)
            matrixA[i][j] = rand();

    srand(time(NULL));
    for (int i = 0; j < M; i++)
        for (int j = 0; j < L; j++)
            matrixB[i][j] = rand();

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