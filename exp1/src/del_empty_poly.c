/* del_empty_poly.c
 * delete or empty a poly node
 */

#include "main.h"
#include "assistant.h"
#include "del_empty_poly.h"

#include <stdio.h>
#include <stdlib.h>

void DelPoly(pList head) {
    int choice = 0;
    printf("Printing out add available polys: \n");
    ShowList(head, 0);
    printf("Enter the number of poly you want to delete: ");
    scanf("%d", &choice);

    /* We need to find the prev ! */
    pPoly p = FindPoly(head, choice - 1);
    pPoly tmp = p->next;
    p->next = tmp->next;
    DestroyPoly(tmp);
    printf("\n\nNow the list is:\n");
    ShowList(head, 0);
    printf("Press ENTER to continue....");
    flush_stdin();
    getchar();
}

void EmptyPoly(pList head) {
    int choice = 0;
    printf("Printing out add available polys: \n");
    ShowList(head, 0);
    printf("Enter the number of poly you want to empty: ");
    scanf("%d", &choice);

    pPoly p = FindPoly(head, choice);
    __empty_poly(p);
    printf("\n\nNow the list is:\n");
    ShowList(head, 0);
    printf("Press ENTER to continue....");
    flush_stdin();
    getchar();
}

void DestroyPoly(pPoly p) {
    pNode n = p->head;
    pNode nnext = NULL;
    while(n != NULL) {
        nnext = n->next;
        free(n);
        n = nnext;
    }
    free(p);
}

void __empty_poly(pPoly p) {
    pNode n = p->head;
    n->coff = 0;
    n->freq = 0;
    pNode nnext = n->next;
    n->next = NULL;
    n = nnext;
    /* Destroy the other nodes */
    while(n != NULL) {
        nnext = n->next;
        free(n);
        n = nnext;
    }
}