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
Queue CreateQueue(void);
void MakeEmpty(Queue Q);
void Enqueue(person x, Queue Q);
person Front(Queue Q);
void Dequeue(Queue Q);
person FrontAndDequeue(Queue Q);
void ExtendQueue(Queue Q);
person FindPerson(Queue Q, int num);

struct QueueRecord {
	person front;
	person rear;
	int size;
};

struct aPerson {
    int num;        // people's tag
    int time;       // entering time
    int deps_money;     // money to do with
    int end;
    person next;
};
#endif // QUEUE_H
