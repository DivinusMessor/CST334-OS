#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define N 10
#define M 10
#define L 10


int main()
{

    double matrixA[N][M];
    double matrixB[M][L];
    double matrixC[N][L];
    int i,j,k;

    srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrixA[i][j] = rand();

    srand(time(NULL));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < L; j++)
            matrixB[i][j] = rand();

    
    // Displaying matA        
    for (i = 0; i < N; i++){
        for(j = 0; j < M; j++)
            printf("%d ", matrixA[i][j]);
        printf("\n");
    }

    printf("-------------------\n");
             
    // Displaying matB               
    for (i = 0; i < M; i++){
        for(j = 0; j < L; j++)
            printf("%d ",matrixB[i][j]);
        printf("\n");   
    }
    
}