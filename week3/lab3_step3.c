/*
# Name: Yukio Rivera
# Date: 3/22/2022 
# Title: Lab 3 – Step3  
# Description: This program is an example using execlp to pipe
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
/*Sample C program for Lab assignment 3*/
// main
int main() {
    int fds[2];
    pipe(fds);
    /*child 1 duplicates downstream into stdin */
        if (fork() == 0) {
            dup2(fds[0], 0);
            close(fds[1]);
            execlp("grep", "grep", "root", 0);
        }
        /*child 2 duplicates upstream into stdout */
        else if (fork() == 0) {
            dup2(fds[1], 1);

            close(fds[0]);
            execlp("cat", "cat", "/etc/passwd", 0);
        }
        else { /*parent closes both ends and wait for children*/
            close(fds[0]);
            close(fds[1]);
            wait(0);
            wait(0);                                                                                                            }           
        return 0;
}
