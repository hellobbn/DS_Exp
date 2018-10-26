#include "main.h"
#include "assistant.h"
#include "common.h"

#include <stdlib.h>
#include <stdio.h>


/* NewListNode(): Make new node for the list */
pList NewListNode(void) {
    pList listNode = malloc(sizeof(struct polyList));
    listNode->head = NULL;
    listNode->next = NULL;
    listNode->coffLn = 0;

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
            if(p->freq == nodeFreq) {
                p->coff += node->coff;
                /* In this situation, the node is note needed anymore*/
                free(node);
                break;
            } else if(p->next != NULL) {
                if(p->next->freq < nodeFreq) {
                    pNode tmp = p->next;
                    p->next = node;
                    node->next = tmp;
                    break;
                }
            } else {
                p->next = node;
                node->next = NULL;
                break;
            }
            p = p->next;
        }
    }

}

/* PrintPoly(): print out the poly */
void PrintPoly(pPoly p) {
    pNode nodePoint = p->head;
    int cnt = 0;

    double lnCoff = p->coffLn;
    if(lnCoff) {
        if(absF(lnCoff - 1) < 10E-3) {
            printf("Ln(x) ");
        } else if(absF(lnCoff + 1) < 10E-3) {
            printf("-Ln(x) ");
        } else {
            printf("%.2fLn(x) ", lnCoff);
        }
        cnt ++;
    }
    while(nodePoint != NULL) {
        /* Print each node */
        if(cnt == 0) {
            if(nodePoint->coff < 0)  {
                printf("-");
            }
            cnt += PrintNode(nodePoint);
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
            cnt += PrintNode(nodePoint);
        }
        nodePoint = nodePoint->next;
    }
    if(cnt == 0) {
        printf("0");
    }
    printf("\n");
}

int PrintNode(pNode n) {
    double a = absF(n->coff);
    int b = n->freq;
    /* Only print out things when a is not equal to 0 */
    if(a != 0) {
        if(b == 0) {
            printf("%.2lf", a);
        } else if(b == 1){
            if(absF(a - 1) < 10E-3) {
                printf("x");
            } else {
                printf("%.2lfx", a);
            }
        } else {
            if(absF(a - 1) < 10E-3) {
                printf("x^%d", b);
            } else {
                printf("%.2lfx^%d", a, b);
            }
        }
        return 1;
    }
    return 0;
}

pPoly FindPoly(pList p, int num) {
    pPoly tmp = p;
    for(int n = 0; n < num; ++ n) {
        if(tmp->next != NULL){
            tmp = tmp->next;
        } else {
            tmp = NULL;
            break;
        }
    }

    return tmp;
}

pNode FindNode(pPoly p, int freq) {
    pNode pointer = p->head;
    while(pointer != NULL) {
        if(pointer->freq == freq) {
            /* We found the node */
            break;
        }
        pointer = pointer->next;
    }
    return pointer;
}

pNode FindPrevNode(pPoly p, int freq) {
    pNode n = p->head;
    while(n->next != NULL) {
        if(n->next->freq == freq) {
            return n;
        } else {
            n = n->next;
        }
    }
    return NULL;
}

int AllowNeg(pPoly p) {
    pNode n = p->head;
    while(n != NULL) {
        if(n->freq < 0) {
            return 0;
        }
        n = n->next;
    }
    return 1;
}

void ClearScreen(void) {
    system("clear");
}

pPoly CopyPoly(pPoly p) {
    pPoly tmp = NewListNode();
    pNode n = p->head;
    while(n != NULL) {
        pNode ntmp = MakeNode();
        ntmp->coff = n->coff;
        ntmp->freq = n->freq;
        InsertNode(ntmp, tmp);
    }
    return tmp;
}

pNode FisrtNZFreq(pPoly p) {
    pNode n = p->head;
    while(n != NULL) {
        if(n->coff == 0) {
            n = n->next;
        } else {
            return n;
        }
    }
    return NULL;
}