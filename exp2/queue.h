
#if !defined(QUEUE_H)
#define QUEUE_H



typedef struct QueueNode QNode;
typedef struct QueueNode* pQNode;
typedef struct LinkedQueue LQueue;
typedef struct LinkedQueue* pLQueue;

struct QueueNode
{
    char c;
    struct QueueNode* next;
};

struct LinkedQueue
{
    struct QueueNode* head;
    struct QueueNode* rear;
};

#endif // QUEUE_H
