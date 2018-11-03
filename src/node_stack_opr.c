#include "main.h"
#include "nodestack.h"

#include <stdlib.h>

pnStack CreatenStack(void) {
    pnStack S;

    S = malloc(sizeof(struct NodeStack));
    if(S) {
        S->next = NULL;
        S->p = NULL;
        return S;
    }
    return NULL;
}

void nPush(pPoly elem, pnStack S) {
    pnStackNode tmp = malloc(sizeof(struct NodeStack));
    tmp->p = elem;
    tmp->next = S->next;
    S->next = tmp;
}

void MakenEmpty(pnStack S) {
    while(!IsnEmpty(S)) {
        nPop(S);
    }
}

pPoly nShowElem(pnStack S) {
    if(S->next != NULL) {
        return S->p;
    }
    return 0;
}

int IsnEmpty(pnStack S) {
    return (S->next == NULL);
}

pPoly nPop(pnStack S) {
    pnStack tmp = S->next;
    if(tmp) {
        S->next = tmp->next;
        return tmp->p;
    }
    return NULL;
}