#include "main.h"
#include "assistant.h"

#include <stdlib.h>
#include <stdio.h>

void PrintNode(pNode n);

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

void ReallocStr(char** s, int len) {
    char* tmp = realloc(*s, len + EACH_INCR_SIZE);
    if(!tmp) {
        printf("Error: In function %s, buffer is full but realloc() failed",\
                            __func__);
        exit(1);
    }
    *s = tmp;
}

/* InsertNode(): Insert new node to the requested poly */
void InsertNode(pNode node, pPoly polyHead) {
    if(polyHead->head == NULL) {
        /* Inserting the first element */
        node->next = NULL;
        polyHead->head =  node;
    } else if(polyHead->head->freq < node->freq) {
        pNode tmp = polyHead->head;
        polyHead->head = node;
        node->next = tmp;
    } else {
        /* find the suitable place to put node */
        pNode p = polyHead->head;
        int nodeFreq = node->freq;
        while(p != NULL) {
            if(p->next != NULL) {
                if(p->next->freq < nodeFreq) {
                    pNode tmp = p->next;
                    p->next = node;
                    node->next = tmp;
                    /* now we have finished the insertion */
                    break;
                }
            } else {
                /* We have reached the final node */
                p->next = node;
                node->next = NULL;
            }
            p = p->next;
        }
    }

}

/* PrintPoly(): print out the poly */
void PrintPoly(pPoly p) {
    pNode nodePoint = p->head;
    int nItem = 0;
    while(nodePoint != NULL) {
        /* Print each node */
        if(nItem == 0) {
            PrintNode(nodePoint);
        } else {
            /* if coff = 0, printNode() could handle it 
             * So there is no need to handle it.
             * Simply skip the condition.
             */
            if(nodePoint->coff > 0) {
                printf(" + ");
            } else if(nodePoint->coff < 0) {
                printf(" - ");
            }
            PrintNode(nodePoint);
        }
        nodePoint = nodePoint->next;
    }
}

void PrintNode(pNode n) {
    double a = n->coff;
    double b = n->freq;
    if(a != 0) {
        if(b == 0) {
            if( ) {
                
            }
        }
    }
}