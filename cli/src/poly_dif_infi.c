/* poly_differential.c
 * Used to calculate the poly differential 
 */

#include "main.h"
#include "assistant.h" 
#include "poly_dif_infi.h"
#include "common.h"
#include "del_empty_poly.h"

#include <stdio.h>
#include <stdlib.h>

void PolyDiF(pList p) {
    printf("Printing out available polys :\n");
    ShowList(p, 0);
    
    int choice;
    int n;
    printf("Enter the number of poly: ");
    scanf("%d", &choice);
    printf("Enter the n: ");
    scanf("%d", &n);

    pPoly inPoly = FindPoly(p, choice);
    if(inPoly) {
        /* Maybe we need a new space to save the poly? */
        pPoly newPoly = NewListNode();
        poly_dif(inPoly, newPoly, n);
        PrintPoly(newPoly);

        printf("Do you want to save it? (y/N)");
        flush_stdin();
        char t = 'N';
        scanf("%c", &t);
        if(t == '\n' || t == 'n' || t == 'N') {
            /* Don't save it, destroy the list */
            DestroyPoly(newPoly);
            return;
        } else if(t == 'y' || t == 'Y') {
            /* Save the poly to the end of the poly list */
            while(p->next != NULL) {
                p = p->next;
            }
            p->next = newPoly;
        } else {
            printf("Invalid Input, skipping....\n");
        }
    }
}

/* Do the actual differential*/
void poly_dif(pPoly in, pPoly out, int n) {
    for(pNode p = in->head; p != NULL; p = p->next) {
        /* p is NOT empty -> make a new node */
        pNode tmp = MakeNode();

        tmp->coff = p->coff;
        tmp->freq = p->freq;
        
        for(int i = 0; i < n; ++ i) {
            tmp->coff *= tmp->freq;
            tmp->freq --;
        }
        InsertNode(tmp, out);
    }
}

void PolyInfI(pList p) {
    printf("Printing out available polys: \n");
    ShowList(p, 0);
    printf("Enter the poly number: ");
    int choice;
    scanf("%d", &choice);

    pPoly n = FindPoly(p, choice);
    if(n) {
        pPoly nPoly = NewListNode();
        poly_infi(n, nPoly);
        PrintPoly(nPoly);

        printf("Do you want to save it? (y/N)");
        char save = 'N';
        scanf("%c", &save);
        if(save == 'n' || save == 'N' || save == '\n') {
            DestroyPoly(nPoly);
        } else if(save == 'y' || save == 'Y') {
            while(p->next != NULL) {
                p = p->next;
            }
            p->next = nPoly;
        } else {
            printf("ERROR: Invalide Input, destroy the node...\n");
            DestroyPoly(nPoly);
        }
    }
}

/* Do the actual infl */
void poly_infi(pPoly in, pPoly out) {
    pNode p = in->head;
    while(p != NULL) {
        pNode tmp = MakeNode();
        tmp->freq = p->freq;
        tmp->coff = p->coff;
        if(tmp->freq == -1) {
            /* We met a node whose infl is a ln 
             * not going to change anything in this node.
             */
            tmp->lnpos = 1;
        } else {
            tmp->freq ++;
            tmp->coff = tmp->coff / tmp->freq;
        }
        InsertNode(tmp, out);
        p = p->next;
    }
}