//# 334 Su 20 Lab 4 queue tester

#include <stdio.h>
#include "queue.h"
#include "node.h"

struct queue *q;

int main(void)   {

    q = queue_create();

    enqueue(q, 99);
    enqueue(q, 201);
    enqueue(q, 1);
    enqueue(q, 22);
    enqueue(q, 33);
    enqueue(q, 69);
    enqueue(q, 21);
    enqueue(q, 2);

    printf("Here are the top %d integers:\n", queue_length(q));
    printf("Content of the queue as follows.\n");
    queue_traverse(q);

    printf("\n");
    printf("Dequeue the first 4\n");
    printf("\n");

    dequeue(q);
    dequeue(q);
    dequeue(q);
    dequeue(q);

    printf("Here are the top %d integers:\n", queue_length(q));
    printf("Content of the queue as follows.\n");
    queue_traverse(q);

    queue_destroy(q);

    return 0;
}
