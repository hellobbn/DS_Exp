/* queue.c
 * functions to operate queue
 */
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

Queue CreateQueue(int MaxElements) {
    Queue q = malloc(sizeof(struct QueueRecord));
    q->arr = malloc(sizeof(struct aPerson) * (MaxElements + 10));
    q->capacity = MaxElements + 10;
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    return q;
}

void Dequeue(Queue Q) {
    if(IsEmpty(Q)) {
        return;
    } else {
        Q->front ++;
        if(Q->front >= Q->capacity) {
            Q->front = 0;
        }
    }
    Q->size --;
}

void Enqueue(person x, Queue Q) {
    if(IsFull(Q)) {
        return;
    } else {
        Q->arr[Q->rear] = x;
        Q->rear ++;
        if(Q->rear == Q->capacity) {
            Q->rear = 0;
        }
    }
    Q->size ++;
}

person Front(Queue Q) {
    if(IsEmpty(Q)) {
        return NULL;
    } else {
        int front = Q->front;
        return Q->arr[front];
    }
}

person FrontAndDequeue(Queue Q) {
    person tmp = Front(Q);
    Dequeue(Q);
    return tmp;
}

int IsEmpty(Queue Q) {
    return (Q->size == 0);
}

int IsFull(Queue Q) {
    return (Q->size == Q->capacity);
}