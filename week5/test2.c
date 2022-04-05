// C Program to multiply two matrix using pthreads without
// use of global variables
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX 4


//Each thread computes single element in the resultant matrix
void *mult(void* arg)
{
	int *data = (int *)arg;
	int k = 0, i = 0;
	
	int x = data[0];
	for (i = 1; i <= x; i++)
		k += data[i]*data[i+x];
	
	int *p = (int*)malloc(sizeof(int));
		*p = k;
	
//Used to terminate a thread and the return value is passed as a pointer
	pthread_exit(p);
}

//Driver code
int main()
{

    #define N 10
    #define M 10
    #define L 10

	int matA[MAX][MAX];
	int matB[MAX][MAX];
    double matrixA[N][M];
    double matrixB[M][L];
    double matrixC[N][L];
	
	
	int r1=MAX,c1=MAX,r2=MAX,c2=MAX,i,j,k;


	srand(time(NULL));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            matrixA[i][j] = rand();
		
		// Generating random values in matB
	for (i = 0; i < r1; i++)
			for (j = 0; j < c1; j++)
				matB[i][j] = rand() % 10;
	
	// Displaying matrixA		
	for (i = 0; i < r1; i++){
		for(j = 0; j < c1; j++)
			printf("%d ",matA[i][j]);
		printf("\n");
	}

    printf("---------------\n");
			
	// Displaying matB			
	for (i = 0; i < r2; i++){
		for(j = 0; j < c2; j++)
			printf("%d ",matB[i][j]);
		printf("\n");
	}
	
	
	int max = r1*c2;
	
	
	//declaring array of threads of size r1*c2	
	pthread_t *threads;
	threads = (pthread_t*)malloc(max*sizeof(pthread_t));
	
	int count = 0;
	int* data = NULL;
	for (i = 0; i < r1; i++)
		for (j = 0; j < c2; j++)
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

	

return 0;
}
