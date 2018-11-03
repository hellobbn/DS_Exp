/* mp_div.c
 * Used for multiplication and division of two polys
 * We could use the DisAndCall() function before
 */

#include "main.h"
#include "assistant.h"
#include "common.h"
#include "del_empty_poly.h"

#include <stdio.h>
#include <stdlib.h>

void do_div(pPoly polyA, pPoly polyB, pPoly s);

pPoly PolyMultip(pPoly polyA, pPoly polyB) {
    pPoly outPoly = NewListNode();
    pNode nodeA = polyA->head;
    pNode nodeB = polyB->head;

    while(nodeA) {
        while(nodeB) {
            pNode nNode = MakeNode();
            nNode->freq = nodeB->freq + nodeA->freq;
            nNode->coff = nodeB->coff * nodeA->coff;
            InsertNode(nNode, outPoly);
            nodeB = nodeB->next;
        }
        nodeB = polyB->head;
        nodeA = nodeA->next;
    }
    return outPoly;
}

void PolyPow(pList p) {
    printf("Enter the NO of poly to pow: \n");
    ShowList(p, 0);
    int choice;
    int n;
    scanf("%d", &choice);
    pPoly pp = FindPoly(p, choice);
    if(pp) {
        printf("ENter n: ");
        scanf("%d", &n);
        pPoly tmp;
        tmp = CopyPoly(pp);
        for(int i = 1; i < n; ++ i) {
            pPoly in = tmp;
            tmp = PolyMultip(tmp, pp);
            DestroyPoly(in);
        }

        PrintPoly(tmp);
    }
    printf("Press ENTER to continue.....");
    flush_stdin();
    getchar();
}

pPoly PolyDiv(pPoly polyA, pPoly polyB) {
    pPoly outPoly = NewListNode();
    do_div(polyA, polyB, outPoly);
    printf("Press ENTER to continue......");
    flush_stdin();
    getchar();
    return NULL;
}

void do_div(pPoly polyA, pPoly polyB, pPoly s) {
    int freqA = polyA->head->freq;
    int freqB = polyB->head->freq;
    pNode k = FisrtNZFreq(polyA);
    if(k) {
        freqA = k->freq;
    } else {
        PrintPoly(s);
        return;
    }
    pNode j = FisrtNZFreq(polyB);

    /* b is not a poly */
    if(j) {
        freqB = j->freq;
    } else {
        printf("ERROR: b is zero!");
        return;
    }
    if(freqA < freqB) {
        printf("\n\n");
        printf("Left: ");
        PrintPoly(polyA);
        printf("Poly: ");
        PrintPoly(s);
    } else {
        // printf("PolyA = ");
        // PrintPoly(polyA);
        // printf("\nPolyB = ");
        // PrintPoly(polyB);
        pPoly tmpPoly = NewListNode();
        double coffA = k->coff;
        double coffB = j->coff;
        pNode n = MakeNode();
        pNode ntmp = MakeNode();
        n->coff = coffA / coffB;
        n->freq = freqA - freqB;
        ntmp->coff = n->coff;
        ntmp->freq = n->freq;
        InsertNode(ntmp, tmpPoly);
        InsertNode(n, s);
        pPoly tmp = PolyMultip(tmpPoly, polyB);
        DestroyPoly(tmpPoly);
        pPoly ttmp = SubPoly(polyA, tmp);
        DestroyPoly(tmp);
        do_div(ttmp, polyB, s);
    }

}