/* solve_poly: 
 * let x = something and solve it!
 */

#include "main.h"
#include "assistant.h"
#include "common.h"

#include <stdio.h>

double __solve_node(pNode n);

double SolvePoly(pList list) {
    int choice = 0;
    double result = 0;
    printf("Printing out available polys: \n");
    ShowList(list, 0);
    printf("Please decide which one to solve: ");
    scanf("%d", &choice);

    /* Find the poly */
    pPoly p = FindPoly(list, choice);
    if(!p) {
        printf("ERROR: poly does not exist!");
    } else {
        pNode pPoint = p->head;
        while(pPoint != NULL) {
            result += __solve_node(pPoint);
        }
    }
}