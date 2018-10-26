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

pPoly PolyDiv(pPoly polyA, pPoly polyB) {
    pPoly outPoly = NewListNode();
    do_div(polyA, polyB, outPoly);

    return outPoly;
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
    if(j) {
        freqB = j->freq;
    } else {
        PrintPoly(polyA);
        return;
    }
    if(freqA < freqB) {
        printf("Left: ");
        PrintPoly(polyA);
        printf("\n");
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