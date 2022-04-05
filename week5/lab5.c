#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

// #define N 10
// #define M 10
// #define L 10
int size = 8;


int main()
{
    
    srand(time(NULL));

    double matrixA[size][size];
    double matrixB[size][size];
    // double matrixC[N][L];
    //int i,j,k;

    
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }

    
    // Displaying matA        
    for (int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            printf("%g ", matrixA[i][j]);
        }
        printf("\n");
    }

    printf("-------------------\n");
             
    // Displaying matB               
    for (int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            printf("%g ",matrixB[i][j]);
        printf("\n");   
    }
   
}