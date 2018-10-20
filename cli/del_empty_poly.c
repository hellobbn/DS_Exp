/* del_empty_poly.c
 * delete or empty a poly node
 */

#include "main.h"
#include "assistant.h"

#include <stdio.h>
#include <stdlib.h>

void DestroyPoly(pPoly p);

void DelPoly(pList head) {
    int choice = 0;
    printf("Printing out add available polys: ");
    ShowList(head, 0);
    printf("Enter the number of poly you want to delete: ");
    scanf("%d", &choice);

    /* We need to find the prev ! */
    pPoly p = FindPoly(head, choice - 1);
    pPoly tmp = p->next;
    p->next = tmp->next;
    DestroyPoly(p);
}

void DestroyPoly(pPoly p) {
    pNode n = p->head;
    pNode nnext = NULL;
    while(n != NULL) {
        nnext = n->next;
        free(n);
        n = nnext;
    }
}