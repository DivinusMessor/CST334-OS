#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {

   int a = 5;

int fd = open(...) //opening a file

int ret = fork();

if (ret > 0) {

   close(fd);

   a = 6;

   ...

}

else if (ret==0) {

   printf("a=%d\n", a);

   read(fd, something);

}

