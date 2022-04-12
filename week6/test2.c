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
pthread_t threads[2];
// #define alphaSize 26
#define buffer 26

char buff[26];
char alpha[NTHREADS];
int fill = 0;
int use = 0;
sem_t mutex;
sem_t empty;
sem_t full;

void put (int value) {
	buff[fill] = value;
	fill = (fill + 1) % 26; // dependant on length of alpha?
}

int get() {
	int tmp = buff[use];
	use = (use + 1) % 26;
	return tmp;
}


void *produce(void *arg) {
	int i; // added to test 

	for (char letter = 'A'; letter <= 'Z'; ++letter) {
		
      //printf("Did it make it %d \n", (int)pthread_self());

		sem_wait(&empty);
		sem_wait(&mutex);

		
		printf("Consumer thread %lu :: buffer >> %c\n", pthread_self(), letter);
      put(letter); // attempt using get
		// printf("Consumer thread %lu :: buffer >> %c\n", pthread_self(), alpha[i]);
		// printf("Thread %c Entered Critical Contition...\n", buff);
		// buff = 0;
		sem_post(&mutex);
		sem_post(&full);
	}
	// moved print line
    return 0;
}

void* consume(void *arg) {
    int tmp = 0;
	
	while (tmp != 90) {
		sem_wait(&full);
		sem_wait(&mutex);

		tmp = get();
		printf("Consumer thread %lu :: buffer >> %c\n", pthread_self(), tmp);
		// printf("Thread %c Entered Critical Contition...\n", buff);
		//buff = 0;

		sem_post(&mutex);
		sem_post(&empty);

	}
	return 0;
}

int main() {
    // Initialize our Semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, buffer);
    sem_init(&full, 0, 0);

    int j = 0;

	// printing letter array 
	printf("Contents of Letter array: ");
    for (char letter = 'A'; letter <= 'Z'; letter++) {
		alpha[j] = letter; 
		printf("%c ", alpha[j]);
		j++;
	}
	

	// space for new line
	printf("\n");
	
    pthread_create(&threads[0], NULL, produce, NULL);
	pthread_create(&threads[1], NULL, consume, NULL);

	pthread_join(threads[0], NULL);
	printf("Producer Thread Ended. \n");

	pthread_join(threads[1], NULL);
	printf("Consumer Thread Returned. \n");

    printf("Main thread done.\n");

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
