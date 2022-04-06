#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//Each thread computes single element in the resultant matrix
void *mult(void* arg)
{
    int *data = (int *)arg;
    int k = 0, i = 0;
     
    int x = data[0];
    for (i = 1; i <= x; i++)
           k += data[i]*data[i+x];
     
    int *p = (int*)malloc(sizeof(double));
        *p = k;
     
//Used to terminate a thread and the return value is passed as a pointer
    pthread_exit(p);
}

int main() {
   	const int gridSize = 3;
   	// const int gridSize = 1024;
    srand(time(NULL));
    int i;
    int j;
    int k;

    // Declare the three matrices
    double** matrixA = (double**)malloc(sizeof(double*) *gridSize);
    double** matrixB = (double**)malloc(sizeof(double*) *gridSize);
    double** matrixC = (double**)malloc(sizeof(double*) *gridSize);
    for (i = 0; i < gridSize; i++) {
        // matrixA[i] = (double*)malloc(sizeof(double)*gridSize);
        // matrixB[i] = (double*)malloc(sizeof(double)*gridSize);
        // matrixC[i] = (double*)malloc(sizeof(double)*gridSize);
        matrixA[i] = (double*)calloc(gridSize*gridSize, sizeof(double));
        matrixB[i] = (double*)calloc(gridSize*gridSize, sizeof(double));
        matrixC[i] = (double*)calloc(gridSize*gridSize, sizeof(double));
    }

    // Generate random numbers for our two matrices
    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridSize; j++) {
            matrixA[i][j] = rand() % 10;
            matrixB[i][j] = rand() % 10;
        }
    }

    // Multi Threaded Multiplication
    // pthread_t p;
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

    int max = gridSize*gridSize;
     
     
    //declaring array of threads of size r1*c2       
    pthread_t *threads;
    threads = (pthread_t*)malloc(max*sizeof(pthread_t));
     
    int count = 0;
    int* data = NULL;
    for (i = 0; i < gridSize; i++)
        for (j = 0; j < gridSize; j++) {
                
               //storing row and column elements in data
            data = (int *)malloc((20)*sizeof(int));
            data[0] = gridSize;
     
            for (k = 0; k < gridSize; k++)
                data[k+1] = matrixA[i][k];
     
            for (k = 0; k < gridSize; k++)
                data[k+gridSize+1] = matrixB[k][j];
              
             //creating threads
                pthread_create(&threads[count++], NULL,
                               mult, (void*)(data));
                 
            }
     
    printf("RESULTANT MATRIX IS :- \n");
    for (i = 0; i < max; i++)
    {
        void *k;
       
        //Joining all threads and collecting return value
        pthread_join(threads[i], &k);
            
           
        int *p = (int *)k;
        
        printf("%d ",*p);
        if ((i + 1) % gridSize == 0)
            printf("\n");
        
    }

    return 0;
}

void* calculate(void* arg) {

}