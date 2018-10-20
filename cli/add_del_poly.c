/* add_del_poly: Add or Sub two requested poly
 * 
 * TODO: Make the two function into one
 */

#include "main.h"
#include "assistant.h"

#include <stdio.h>
#include <stdlib.h>

pPoly AddPoly(pPoly a, pPoly b) {
    /* 1. Copy all node of a to a new poly p
     * 2. Use InsertPoly to insert each poly to p
     * 3. Note that we should make a copy first
     */
    pNode tmp = a->head;
    pList p = NewListNode();
    pNode ppos = p->head;
    while(tmp != NULL) {
        if(p->head == NULL) {
            p->head = MakeNode();
            ppos = p->head;
            ppos->coff = tmp->coff;
            ppos->freq = tmp->freq;
        } else {
            ppos->next = MakeNode();
            ppos->next->coff = tmp->coff;
            ppos->next->freq = tmp->freq;
            ppos = ppos->next;
            ppos->next = NULL;
        }
        tmp = tmp->next;
    }

    tmp = b->head;
    while(tmp != NULL) {
        pNode ptmp = MakeNode();
        ptmp->coff = tmp->coff;
        ptmp->freq = tmp->freq;
        InsertNode(ptmp, p);
        tmp = tmp->next;
    }

    return p;
}

pPoly SubPoly(pPoly a, pPoly b) {
    /* SubPoly() is almost the same as AddPoly()
     * The only difference is that we need to *(-1)
     * for b's coff
     */
    pNode tmp = a->head;
    pList p = NewListNode();
    pNode ppos = p->head;
    while(tmp != NULL) {
        if(p->head == NULL) {
            p->head = MakeNode();
            ppos = p->head;
            ppos->coff = tmp->coff;
            ppos->freq = tmp->freq;
        } else {
            ppos->next = MakeNode();
            ppos->next->coff = tmp->coff;
            ppos->next->freq = tmp->freq;
            ppos = ppos->next;
            ppos->next = NULL;
        }
        tmp = tmp->next;
    }

    tmp = b->head;
    while(tmp != NULL) {
        pNode ptmp = MakeNode();
        ptmp->coff = -1 * tmp->coff;
        ptmp->freq = tmp->freq;
        InsertNode(ptmp, p);
        tmp = tmp->next;
    }

    return p;
}