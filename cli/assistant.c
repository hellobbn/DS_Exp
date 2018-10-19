#include "main.h"
#include "assistant.h"

#include <stdlib.h>
#include <stdio.h>

/* NewListNode(): Make new node for the list */
pList NewListNode(void) {
    pList listNode = malloc(sizeof(struct polyList));
    listNode->head = MakeNode();
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

void ReallocStr(char** s, int len) {
    char* tmp = realloc(*s, len + EACH_INCR_SIZE);
    if(!tmp) {
        printf("Error: In function %s, buffer is full but realloc() failed",\
                            __func__);
        exit(1);
    }
    *s = tmp;
}
