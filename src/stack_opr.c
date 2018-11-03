#include "stack.h"

#include <stdlib.h>

pStack CreateStack(void) {
    pStack S;

    S = malloc(sizeof(struct StackNode));
    if(S) {
        S->next = NULL;
        S->num = 0;
        return S;
    }
    return NULL;
}

void MakeEmpty(pStack S) {
    while(!IsEmpty(S)) {
        Pop(S);
    }
}
void Push(char elem, pStack S) {
    pStackNode tmp = malloc(sizeof(struct StackNode));
    tmp->num = elem;
    tmp->next = S->next;
    S->next = tmp;
}

char ShowElem(pStack S) {
    if(S->next != NULL) {
        return S->next->num;
    }
    return 0;
}

int IsEmpty(pStack S) {
    if(S->next == NULL) {
        return 1;
    }
    return 0;
}

char Pop(pStack S) {
    pStack tmp = S->next;
    if(tmp) {
        S->next = tmp->next;
        return tmp->num;
    }
    return 0;
}