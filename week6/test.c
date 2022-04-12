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
pthread_t threads[2];

char letters[NTHREADS];
char buffer[26];
int fill = 0;
int use = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void put(int value)
{
   buffer[fill] = value;
   fill = (fill+1) % 26;
}
int get()
{
   int tmp = buffer[use];
   use = (use + 1) % 26;
   return tmp;
}

//Producer thread
void * producer(void *arg)
{
    int i;
    for(char alpha = 'A'; alpha <= 'Z'; alpha++)
    {
     //int i = *((int*)arg);
      //do {
     // produce next item ...

      sem_wait(&empty);
      sem_wait(&mutex);
      put(alpha);
      //add the item to buffer
      printf("Producer Thread %lu :: %c >> buffer \n" , pthread_self(), alpha);
      sem_post(&mutex);
      sem_post(&full);
   } 
   return NULL;
}


void *consumer(void *arg)
{
   //Consumer thread
   int tmp = 0;
   while(tmp != 90)
   {
      sem_wait(&full);
      sem_wait(&mutex);
      //printf("LETTER: %c\n", buffer);
     // remove next item from buffer ...
      tmp = get(); 
      printf("Consumer thread %lu :: buffer >> %c\n", pthread_self(), tmp);
      sem_post(&mutex);
      sem_post(&empty);
} 
  return NULL;
}

int main()
{
   sem_init(&mutex, 0, 1);
   sem_init(&empty, 0, BufferSize);
   sem_init(&full, 0, 0);

   int i = 0;
   printf("Contents of letter array: ");
   for(char alphabet = 'A'; alphabet <= 'Z'; ++alphabet){
      letters[i] = alphabet;
      printf("%c ", letters[i]);
      i++;
   }
   pthread_create(&threads[0], NULL, producer, NULL);

   pthread_create(&threads[1], NULL, consumer, NULL);
       
   pthread_join(threads[0], NULL);
   printf("Producer Thread Ended. \n");
   pthread_join(threads[1], NULL);
   printf("Consumer Thread Ended. \n");
   sem_destroy(&mutex);
   sem_destroy(&full);
   sem_destroy(&empty);
   
 return 0;
}