/**********************************************************************************
# Name: Yukio Rivera
# Date: 4/12/2022
# Title: Lab 6
# Description: Step 2 adding the producer/consumer 
**********************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 26
pthread_t threads[52];
// #define alphaSize 26
#define buffer 1

char buff;
char alpha[NTHREADS];
sem_t mutex;
sem_t empty;
sem_t full;

void* produce(void *arg) {
    int i = *((int*)arg);
    // printf("From main %i \n", i); // debugging 

    sem_wait(&empty);
    sem_wait(&mutex);

	printf("Producer thread %lu :: %c >> buffer\n", pthread_self(), alpha[i]);
    buff = alpha[i];
    
    sem_post(&mutex);
    sem_post(&full);

    return 0;
}

void *consume(void *arg) {
	int i = *((int*)arg); // added to test 

    sem_wait(&full);
    sem_wait(&mutex);

	printf("Consumer thread %lu :: buffer >> %c\n", pthread_self(), alpha[i]);
    // printf("Thread %c Entered Critical Contition...\n", buff);
    buff = 0;

    sem_post(&mutex);
    sem_post(&empty);

    return 0;
}

int main() {
    // Initialize our Semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, buffer);
    sem_init(&full, 0, 0);
    int blocker[52];

    int j = 0;

	// printing letter array 
	printf("Contents of Letter array: ");
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        alpha[j++] = letter; 
		printf("%c ", letter);
    }

	// space for new line
	printf("\n");
	
	
	
 
    for (int i = 0; i < NTHREADS; i++) {
        blocker[i] = i;
        pthread_create(&threads[i], NULL, produce, &blocker[i]);
        // pthread_create(&threads[i], NULL, produce, (void *)(size_t)i);
        pthread_create(&threads[i + 26], NULL, consume, &blocker[i]);
		
		// Printing char getting into buffer
		// printf("Producer thread %lu :: %c >> buffer\n", threads, alpha[i]);
    }

    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
        // printf("Thread %d returned \n", alpha[i]);

        pthread_join(threads[i + 26], NULL);
        int temp = i + 26;
        //printf("Thread %d returned \n", alpha[temp]);

		// Printing char getting out of buffer 
		// printf("Consumer thread %lu :: buffer >> %c\n", threads, alpha[i]);
    }

    printf("Main thread done.\n");

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
