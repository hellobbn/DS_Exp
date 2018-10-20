/* solve_poly: 
 * let x = something and solve it!
 */

#include "main.h"
#include "assistant.h"
#include "common.h"

#include <stdio.h>

double __solve_node(pNode n, double x);

double SolvePoly(pList list) {
    int choice = 0;
    double result = 0;
    double x = 0;
    printf("Printing out available polys: \n");
    ShowList(list, 0);
    printf("Please decide which one to solve: ");
    scanf("%d", &choice);
    printf("Enter the num of x: ");
    scanf("%le", &x);

    /* Find the poly */
    pPoly p = FindPoly(list, choice);
    if(!p) {
        printf("ERROR: poly does not exist!");
    } else {
        pNode pPoint = p->head;
        while(pPoint != NULL) {
            result += __solve_node(pPoint, x);
            pPoint = pPoint->next;
        }
    }

    printf("f(%.2lf) = %.2lf\n", x, result);
}

double __solve_node(pNode n, double x) {
    double coff = n->coff;
    int freq = n->freq;
    return coff * PoW(x, freq);
}