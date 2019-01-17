/* queue.h
 * header for queue
 * define the queue structure and functions
 */


#if !defined(QUEUE_H)
#define QUEUE_H

typedef struct aQueue* Queue;
typedef struct QueueNode* pQNode;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(void);
void MakeEmpty(Queue Q);
void Enqueue(pQNode x, Queue Q);
pQNode Front(Queue Q);
void Dequeue(Queue Q);
pQNode FrontAndDequeue(Queue Q);

struct aQueue {
    int size;       // size of queue
    pQNode front;
    pQNode rear;
};
struct QueueNode {
    int x, y;
    struct QueueNode* next;
    struct QueueNode* ances;
};
#endif // QUEUE_H
