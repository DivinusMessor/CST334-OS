#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_COUNT 500
#define BUF_SIZE 100

int x;

void main(void) {
	fork();

        fork();
}
