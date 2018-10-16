#include "main.h"

#include <stdlib.h>
#include <stdio.h>

/* NewListNode(): Make new node for the list */
pList NewListNode(void) {
    pList listNode = malloc(sizeof(struct polyList));
    listNode->head = NULL;
    listNode->next = NULL;

    return listNode;
}

/* MakeNode(): Make new node for the polynomial */
pNode MakeNode(void) {
    pNode p = malloc(sizeof(struct polyNode));
    p->coff = 0.0;
    p->freq = 0;
    p->next = NULL;
    return p;
}
 
/* flush_stdin(): make stdin empty */
void flush_stdin(void) {
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}
