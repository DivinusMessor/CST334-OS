/*
# Name: Yukio Rivera
# Date: 3/15/2022
# Title: Lab 2 – Step5
# Description: This program is an example of parent/child process with 
# the added command of ls requested by the asssingment 
*/

#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pid_t pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    printf("\n Before forking.\n");
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "can't fork, error %d\n", errno);
    }
	// If the pid shows the child process then it does the ls command 
    else if(pid == 0) {
        execlp("/bin/ls", "ls", NULL);
    }
	// Waits for the child process to end 
    else {
        wait(NULL);
        printf("Child Complete\n");
        exit(0);
    }
}
