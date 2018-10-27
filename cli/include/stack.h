#if !defined(STACK_H)
#define STACK_H

#include "main.h"

typedef struct StackNode nStack;
typedef struct StackNode* pStack;
typedef struct StackNode* pStackNode;

pStack CreateStack(void);
void MakeEmpty(pStack S);
int IsEmpty(pStack S);
void Push(char elem, pStack S);
char ShowElem(pStack S);
char Pop(pStack S);

struct StackNode {
    char num;
    struct StackNode* next;
};

#endif // STACK_H
