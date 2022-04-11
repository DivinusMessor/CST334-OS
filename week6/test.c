#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
// maximun size of integers to produce and consume
#define MAX 26 // Create the producer and consumer threads

pthread_t prod;
pthread_t cons;
// alphabet buffer
int buffer[MAX];
// utilized ASCII value for "A" - 65 to start to fill the buffer
int start = 65;
// Variables to keep track of buffer
int fill = 0;
int use = 0;
int loc = 0;
// declare semaphores
sem_t empty;
sem_t full;
sem_t mutex;
// Function declarations
void put(int value);
int get();
void *producer(void *arg);
void *consumer(void *arg);
int main()
{
   // Initiate semaphores
   sem_init(&empty, 0, MAX);
   sem_init(&full, 0, 0);
   sem_init(&mutex, 0, 1);

   // Initiate threads
   pthread_create(&prod, NULL, producer, NULL);
   pthread_create(&cons, NULL, consumer, NULL);
   // Join threads
   pthread_join(prod, NULL);
   pthread_join(cons, NULL);

   // Destroy semaphores
   sem_destroy(&empty);
   sem_destroy(&full);
   sem_destroy(&mutex);
   return 0;
}
// Adds value to buffer
void put(int value)
{
   buffer[fill] = value;
   fill = (fill + 1) % MAX;
}
// Gets value from buffer
int get()
{
   int temp = buffer[use];
   use = (use + 1) % MAX;
   return temp;
}
// producer function for thread. Semaphores keep consumer thread away from buffer until its full
void *producer(void *arg)
{
   for (int i = 0; i < MAX; i++)
   {
      sem_wait(&empty);
      sem_wait(&mutex);
      put(start);
      // Prints int item being produce as "char" to make it an alphabet character
      printf("Producer Inserted Item %c at %d\n", start, i);
      start = start + 1;
      sem_post(&mutex);
      sem_post(&full);
   }
}
// consumer function for thread. Semaphre kees producer thread away
void *consumer(void *arg)
{
   for (int i = 0; i < MAX; i++)
   {
      sem_wait(&full);
      sem_wait(&mutex);
      int tmp = get();
      // prints int item being consumed as "char" to make it an alphabet character
      printf("Consumer Removed Item %c from %d\n", tmp, i);
      sem_post(&mutex);
      sem_post(&empty);
   }
}