//Shared data: semaphore full, empty, mutex;
//pool of n buffers, each can hold one item
//mutex provides mutual exclusion to the buffer pool //empty and full count the number of empty and full buffers 
//Initially: full = 0, empty = n, mutex = 1
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#define NTHREADS 26
#define BufferSize 1
pthread_t threads[52];
sem_t empty;
sem_t full;
sem_t mutex;
char alphabet[52];
int buffer;
//Producer thread
void *producer(void *arg)
{
     int i = *((int*)arg);
    //  do {
     // produce next item ...
      
      sem_wait(&empty);
      sem_wait(&mutex);
    
      //add the item to buffer
      buffer = alphabet[i];
      sem_post(&mutex);
      sem_post(&full);
  // } while (1);
  
   return NULL;
}


void *consumer(void *arg)
{
   //Consumer thread
   //
   // do {
      sem_wait(&full);
      sem_wait(&mutex);
      printf("LETTER: %c\n", buffer);
     // remove next item from buffer ...
      buffer = 0; 
      sem_post(&mutex);
      sem_post(&empty);
//} while (1);
  return NULL;
}

int main()
{
   sem_init(&mutex, 0, 1);
   sem_init(&empty, 0, 1);
   sem_init(&full, 0, 0);
   int check[52];
   int k = 0;
   char alpha;
   for(alpha = 'A'; alpha <= 'Z'; ++alpha)
   {
      alphabet[k++] = alpha;
   }
   int i;
   for(i = 0; i < NTHREADS; i++)
   { 
       check[i] = i;
       pthread_create(&threads[i], NULL, producer, &check[i]);
       pthread_create(&threads[i+26], NULL, consumer, &check[i]);
   }
   for(i =0; i < NTHREADS; i++)
   {
      pthread_join(threads[i], NULL);
      pthread_join(threads[i + 26], NULL);
   }
   sem_destroy(&empty);
   sem_destroy(&full);
   sem_destroy(&mutex);
   
 return 0;
}