/*
# Name: Yukio Rivera
# Date: 4/5/2022
# Title: Lab 5 
# Description: Using threads to multiply 2 matrix
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define matrixSize 1024
#define NTHREADS matrixSize
pthread_t threads[NTHREADS];

// Initialize all matrices
double matrixA[matrixSize][matrixSize];
double matrixB[matrixSize][matrixSize];
double matrixC[matrixSize][matrixSize];

void* matrixMath(void* arg) {
    int fromMain = *((int*)arg); // int addr

    // Code base provided by prof 
    for (int i = 0; i < matrixSize; i++) {
        double result = 0;
        for (int j = 0; j < matrixSize; j++) {
            result += matrixA[fromMain][j] * matrixB[j][i];
        }
        matrixC[fromMain][i] = result;
    }

    return 0;
}


int main() {
    // Initialize Random generator
    srand(time(NULL));
    int check[NTHREADS];

    // Initiate 3 matrices
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
            matrixC[i][j] = 0;
        }
    }

    printf("\n"); // empty line 

    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; ++j)
        {
            if (j == (matrixSize - 1))
            {
                printf(" %g ", matrixA[i][j]);
                printf("\n");
            }
            else
            {
                printf(" %g ", matrixA[i][j]);
            }
        }
    }

    printf("\n");

    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; ++j)
        {
            if (j == (matrixSize - 1))
            {
                printf(" %g  ", matrixB[i][j]);
                printf("\n");
            }
            else
            {
                printf(" %g ", matrixB[i][j]);
            }
        }
    }

    printf("\n");

    // Threads to perform computation
    for (int i = 0; i < NTHREADS; i++) {
        // wrap value in arr to pass it to the thread function
        check[i] = i;
        // thread create 
        pthread_create(&threads[i], NULL, matrixMath, &check[i]);
    }

    // Rejoin Threads
    for (int j = 0; j < NTHREADS; j++) {
        pthread_join(threads[j], NULL);
    }

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (j == (matrixSize - 1)) {
                printf(" %g ", matrixC[i][j]);
                printf("\n");
            } else if (j == 0) {
                printf(" %g ", matrixC[i][j]);
            } else {
                printf(" %g ", matrixC[i][j]);
            }
        }
    }
}  
