#include "stack.h"
#include <stdlib.h>


pStack InitStack(void) {
    pStack p;
    p = malloc(sizeof(Stack));
    p->next = NULL;
    p->c = '\0';
    return p;
}

void Push(char c, pStack S) {
    pStack p = InitStack();
    p->c = c;
    p->next = S->next;
    S->next = p;
}

char Pop(pStack S) {
    char c;
    pStack p = S->next;
    c = p->c;
    S->next = p->next;
    free(p);
    return c;
}