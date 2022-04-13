/**********************************************************************************
# Name: Yukio Rivera
# Date: 4/12/2022
# Title: Lab 6
# Description: Step 2 adding the producer/consumer and printing alphabet
**********************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 26
// buffer for the producer and consumer to interact with 
#define buffer 1

// threads for the consumer and producer
pthread_t threads[2];

// initializing 
char buff[26];
char alpha[NTHREADS];
int fill = 0;
int use = 0;
sem_t mutex;
sem_t empty;
sem_t full;

// put that is used by producer
void put (int value) {
	buff[fill] = value;
	fill = (fill + 1) % 26; 
}

// get that is used by consumer 
int get() {
	int tmp = buff[use];
	use = (use + 1) % 26;
	return tmp;
}

// Producer function that adds letter to buffer
void *produce(void *arg) {
	int i; 

	for (i = 0; i < 26; i++) {
		
		sem_wait(&empty);
		sem_wait(&mutex);

		put(alpha[i]); 
		// Print that displays the produced letter 
		printf("Producer thread %lu :: %c >> buffer\n", pthread_self(), alpha[i]);

		sem_post(&mutex);
		sem_post(&full);
	}
	// moved print line
    return 0;
}

// Consumer function that removes letter from buffer
void* consume(void *arg) {
    int tmp = 0;
	
	while (tmp != 90) {
		sem_wait(&full);
		sem_wait(&mutex);

		tmp = get();
		// Print that displays the consumed letter
		printf("Consumer thread %lu :: buffer >> %c\n", pthread_self(), tmp);

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

	// printing letter array and populate array
	printf("Contents of Letter array: ");
    for (char letter = 'A'; letter <= 'Z'; letter++) {
		alpha[j] = letter; 
		printf("%c ", alpha[j]);
		j++;
	}
	

	// space for new line
	printf("\n");
	
	// 2 threads that are used 
   	pthread_create(&threads[0], NULL, produce, NULL);
	pthread_create(&threads[1], NULL, consume, NULL);

	pthread_join(threads[0], NULL);
	printf("Producer Thread Ended. \n");

	pthread_join(threads[1], NULL);
	printf("Consumer Thread Ended. \n");

    printf("Main thread done.\n");

	// Destroying the semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
