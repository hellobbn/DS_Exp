/* queue.c
 * functions to operate queue
 */
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

Queue CreateQueue(void) {
    Queue q = malloc(sizeof(struct aQueue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

void Dequeue(Queue Q) {
    if(IsEmpty(Q)) {
        return;
    } else {
        pQNode p = Q->front;
        Q->front = Q->front->next;
        Q->size --;
        free(p);
        if(Q->front == NULL) {
            Q->rear = NULL;
        }
    }
}

void Enqueue(pQNode x, Queue Q) {
    if(Q->size == 0) {
        Q->front = x;
        Q->rear = x;
    } else {
        Q->rear->next = x;
        Q->rear = x;
    }
    Q->size ++;
}

pQNode Front(Queue Q) {
    if(IsEmpty(Q)) {
        return NULL;
    } else {
        pQNode fnt = Q->front;
        return fnt;
    }
}

pQNode FrontAndDequeue(Queue Q) {
    pQNode fnt = Q->front;
    Q->front = Q->front->next;
    Q->size --;
    return fnt;
}

int IsEmpty(Queue Q) {
    return (Q->size == 0);
}

pQNode FindPerson(Queue Q, int num) {
    int cnt = 0;
    pQNode p = Q->front;
    while(cnt < num) {
        p = p->next;
        cnt ++;
    }

    return p;
}