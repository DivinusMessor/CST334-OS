#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

// #define N 10
// #define M 10
// #define L 10
int size = 8;
int i, j, k;


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

    int max = size*size;
     
     
    //declaring array of threads of size r1*c2       
    pthread_t *threads;
    threads = (pthread_t*)malloc(max*sizeof(pthread_t));
     
    int count = 0;
    int* data = NULL;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
               {
                
               //storing row and column elements in data
            data = (int *)malloc((20)*sizeof(int));
            data[0] = c1;
     
            for (k = 0; k < c1; k++)
                data[k+1] = matA[i][k];
     
            for (k = 0; k < r2; k++)
                data[k+c1+1] = matB[k][j];
              
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
      if ((i + 1) % c2 == 0)
          printf("\n");
    }
    
}