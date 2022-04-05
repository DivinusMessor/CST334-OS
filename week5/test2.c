#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int main() {
    const int gridSize = 3;
    // const int gridSize = 1024;
    srand(time(NULL));
    int i;
    int j;

    // Declare the three matrices
    double** matrixA = (double**)malloc(sizeof(double*) *gridSize);
    double** matrixB = (double**)malloc(sizeof(double*) *gridSize);
    double** matrixC = (double**)malloc(sizeof(double*) *gridSize);
    for (i = 0; i < gridSize; i++) {
        matrixA[i] = (double*)malloc(sizeof(double)*gridSize);
        matrixB[i] = (double*)malloc(sizeof(double)*gridSize);
        matrixC[i] = (double*)malloc(sizeof(double)*gridSize);
    }

    // Generate random numbers for our two matrices
    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridSize; j++) {
            matrixA[i][j] = rand();
            matrixB[i][j] = rand();
        }
    }

    //  Multi Threaded Multiplication
    pthread_t p;
    // double toCalc[gridSize*2];
    // printf("VAL TEST: ", toCalc[(gridSize*2)-1]);
    // pthread_create(&p, NULL, calculate, );

    // DISPLAY section
    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridSize; ++j) {
            if (j == (gridSize - 1)) {
                printf(" %g |", matrixA[i][j]);
                printf("\n");
            } else {
                printf(" %g ", matrixA[i][j]);
            }
        }
    }

    printf("============ \n");

    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridSize; ++j) {
            if (j == (gridSize - 1)) {
                printf(" %g |", matrixB[i][j]);
                printf("\n");
            } else {
                printf(" %g ", matrixB[i][j]);
            }
        }
    }

    printf("============ \n");

    // for (i = 0; i < gridSize; i++) {
    //     for (j = 0; j < gridSize; ++j) {
    //         if (j == (gridSize - 1)) {
    //             printf(" %g |", matrixC[i][j]);
    //             printf("\n");
    //         } else {
    //             printf(" %g ", matrixC[i][j]);
    //         }
    //     }
    // }

    return 0;
}

void* calculate(void* arg) {

}