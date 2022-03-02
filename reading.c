#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "commom.h"
#include "common_threads.h"

volatile int counter = 0;
int loops;

void *worker(void arg) {
	int i;
	for (i = 0; i < loops; i++) {
		counter++;
	}
	return NULL;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: threads <value>\b");
		exit(1);
	}
	loops = atoi(argv[1]);
	pthread_t p1, p2;
	printf("initial value : %d\n", counter);
	Pthread_create(&p1, NULL, worker, NULL);
	Pthread_create(&p2, NULL);
	return 0;
}

