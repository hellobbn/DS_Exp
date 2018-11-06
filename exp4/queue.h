/* queue.h
 * header for queue
 * define the queue structure and functions
 */


#if !defined(QUEUE_H)
#define QUEUE_H

typedef struct QueueRecord* Queue;
typedef struct aPerson* person;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreateQueue(int MaxElements);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(person x, Queue Q);
person Front(Queue Q);
void Dequeue(Queue Q);
person FrontAndDequeue(Queue Q);
void ExtendQueue(Queue Q);

struct QueueRecord
{
	int capacity;
	int front;
	int rear;
	int size;
	person* arr;
};

struct aPerson {
    int num;        // people's tag
    int time;       // entering time
    int deps_money;     // money to do with
    int waiting_time;   // waiting time
};
#endif // QUEUE_H
