/******************/
/* PRIORITY QUEUE */
/******************/

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

/*
	Initialise the priority queue to empty.
	Return value is a pointer to a new priority queue structure.
	This should be free'd by calling pq_destroy.
*/
struct priority_queue *pq_create()
{
	/*create pointer to a new priority queue*/
    pq_t *new;
    /*allocate memory for heapnode array here*/
    new = malloc(sizeof(pq_t));
    new->heap = malloc(sizeof(struct heapnode) * HEAP_ARRAY_SIZE);
    new->heap[0].val = HEAP_ARRAY_SIZE;
    new->size = 0;
	return new;
}


/*
	Cleanup the priority queue and free any memory within.	
*/
void pq_destroy(struct priority_queue *pq)
{
    /*create pointer to queue in memory, free the heap array first and then free the ptr*/
	pq_t *ptr;
    ptr = pq;
    
    free(ptr->heap);
    free(ptr);
	return;
}


/*
	Return the number of elements in the priority queue.
	This is needed to test the priority queue.
	returns: int, the size of the pq
*/
int pq_size(struct priority_queue *pq) {
	return pq->size;
}


/*
	Insert a value with attached min.prority in the priority queue.
	priority should be non-negative (>= 0)
	returns: 1 if successful, 0 if failed (pq is full)
*/
int pq_enqueue(struct priority_queue *pq, int val, int priority)
{
    
    if (priority < 0){
        return 0;
    }
    
    if (pq->size > HEAP_ARRAY_SIZE){
        printf("Error: Queue full!\n");
        return 0;
    }
    else {
        /*we are right to insert*/
        struct heapnode new;
        /*set variables*/
        new.val = val;
        new.priority = priority;
        pq->size++;
        pq->heap[pq_size(pq)] = new;
        
        
        /*Maintain the heap property*/
        int i;
        for (i = (pq->size/2); i >= 1; i--){
            /*the following line passes test 7 but breaks test 4*/
            /*pq_swap(pq, 1, i);*/
            heapify(pq, i);
        
        }
    
    }
    return 1;
}

/*
	Return the value with the lowest priority in the queue.
	This keeps the value stored within the priority queue.
	returns: 1 if successful, 0 if failed (pq is empty)
	val and priority are returned in the pointers
*/	
int pq_find(struct priority_queue *pq, int *val, int *priority)
{
    if (pq->size == 0){
        return 0;
    }
    *val = pq->heap[1].val;
    *priority = pq->heap[1].priority;
	return 1;
}

/*
	Removes the lowest priority object from the priority queue
	returns: 1 if successful, 0 if failed (pq is empty)

	note: may remove this from the spec (do cleanup)
*/
int pq_delete(struct priority_queue *pq)
{
	if (pq_size(pq) == 0){
        return 0;
    }
    
    /*need to remove the first element of the array*/
    pq->heap[1] = pq->heap[pq_size(pq)-1];
    pq->size--;

    /*maintain the heap property*/
    heapify(pq, 1);
    
	return 1;
}


/*
	Returns the value with the lowest priority and removes it
	from the queue.
	This is the same as pq_find followed by pq_delete.
	returns: 1 if successful, 0 if failed (pq is empty)
	val and priority are returned in the pointers
*/	
int pq_dequeue(struct priority_queue *pq, int *val, int *priority)
{
    if (pq_size(pq) == 0){
        return 0;
    }
	
    pq_find(pq, val, priority);
    pq_delete(pq);
	return 1;
}

/*
	Compares two pq elements with each other.
	This is needed to test the heap contained within.
	returns: <0 if a < b, >0 if a > b, 0 if a == b
	note that the root of the heap is at index 1, not zero
*/
int pq_cmp(struct priority_queue *pq, int a, int b)
{
    if (pq->heap[a].priority < pq->heap[b].priority){
        return -1;
    }
    else if (pq->heap[a].priority > pq->heap[b].priority){
        return 1;
    }
    return 0;
}

/*
	Swaps two pq elements with each other.
	This is an internal function that will help with the heap.
*/
void pq_swap(struct priority_queue *pq, int a, int b)
{
	/* you will need to implement this */
    struct heapnode temp;
    temp = pq->heap[a];
    pq->heap[a] = pq->heap[b];
    pq->heap[b] = temp;
	return;
}

void print_pq(struct priority_queue *pq){

    int i;
    for (i = 1; i < pq->size; i++){
        printf("Priority of element %i is %i\n", i, pq->heap[i].priority);
    }
    printf("\n");
    
}

void heapify(struct priority_queue *pq, int i){
    
    int l = 2*i;
    int r = (2*i) + 1;
    int min = 0;
    /*if the left node is less than the parent node, store it at min*/
    if (l <= pq_size(pq) && pq_cmp(pq, l, i) < 0){
        min = l;
        
    }else{
        /*if not, store parent node*/
        min = i;
    }
    /*if the right node is less than the parent node, store it at min*/
    if (r <= pq_size(pq) && pq_cmp(pq, r, min) < 0){
        min = r;
    
    }

    if (min != i){
        pq_swap(pq, min, i);
        heapify(pq, min);
    }
}



