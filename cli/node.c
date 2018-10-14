#include "main.h"

#include <stdlib.h>

pList NewListNode(void) {
    pList listNode = malloc(sizeof(struct polyList));
    listNode->head = NULL;
    listNode->next = NULL;

    return listNode;
}