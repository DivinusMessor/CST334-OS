// CST 334 Lab 4 – FIFO Page Replacement Simulation File I/O 
// Template

/*
# Name: Yukio Rivera
# Date: 3/22/2022
# Title: Lab 4 
# Description: Gain experience with page replacement
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "node.h"

struct queue *q;

typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int C_SIZE = atoi(argv[1]); // Size of Cache passed by user 
    ref_page cache[C_SIZE]; // Cache that stores pages 
    char pageCache[100]; // Cache that holds the input from test file

    q = queue_create(); // queue that I created 
    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int totalAccesses = 0;
    int totalHits = 0;
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array  
        cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); //Stores number read from file as int
        totalAccesses++;
		
		if (!queue_find(q, page_num)){
        
            if (C_SIZE == queue_length(q)){
                dequeue(q);
            }
            totalFaults++;
            enqueue(q, page_num);

        } else {
            totalHits++;
        }
    }

    float hitRate = ((float)totalHits/(float)totalAccesses) * 100;
    printf(
    "%d Total Accesses, %d Total Hits, %d Total Page Faults, %2.2f%% Hit Rate.\n", 
    totalAccesses, totalHits, totalFaults, hitRate);
    
    queue_destroy(q);
    return 0;
}
