/* queue.c
 * functions to operate queue
 */
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

Queue CreateQueue(void) {
    Queue q = malloc(sizeof(struct QueueRecord));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void Dequeue(Queue Q) {
    if(IsEmpty(Q)) {
        return;
    } else {
        person p = Q->front;
        Q->front = Q->front->next;
        Q->size --;
        free(p);
    }
}

void Enqueue(person x, Queue Q) {
    if(Q->size == 0) {
        Q->front = x;
        Q->rear = x->next;
    } else {
        Q->rear = x;
        Q->rear = Q->rear->next;
    }
    Q->size ++;
}

person Front(Queue Q) {
    if(IsEmpty(Q)) {
        return NULL;
    } else {
        person fnt = Q->front;
        return fnt;
    }
}

person FrontAndDequeue(Queue Q) {
    person fnt = Q->front;
    Q->front = Q->front->next;
    Q->size --;
    return fnt;
}

int IsEmpty(Queue Q) {
    return (Q->size == 0);
}
