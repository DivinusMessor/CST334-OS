#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main()
{
   int i;
   int catch[NTHREADS];
   for (i = 0; i < NTHREADS; i++){
      catch[i] = i;
      pthread_create(&threads[i], NULL, go, &catch[i]);
   }
   for (i = 0; i < NTHREADS; i++)
   {
      printf("Thread %d returned\n", i);
      pthread_join(threads[i], NULL);
   }
   printf("Main thread done.\n");
   return 0;
}
void *go(void *arg)
{
   printf("Hello from thread %d with iteration %d\n", (int)pthread_self(), *(int *)arg);
   return 0;
}