#if !defined(STACK_H)
#define STACK_H

/* Typedef */
typedef struct LinckedStack Stack;
typedef struct LinckedStack* pStack;

/* Function */
pStack InitStack(void);
void Push(char c, pStack S);
char Pop(pStack S);

/* Stack */
struct LinckedStack
{
    char c;
    struct LinckedStack* next;
};

#endif // STACK_H
