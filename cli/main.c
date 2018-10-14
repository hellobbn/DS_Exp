/* main.c
 * Implementing basic user interface and 
 * call other functions to achieve different 
 * operations.
*/

#include "main.h"

#include <stdio.h>
#include <stdlib.h>


/* Function used in this file */
pList InitList(void);
int DoOperation(int, pList);

/* Main function */
int main(int argc, char const *argv[])
{

    /* The choosing menu should run in a loop. */
    while(1) {
        /* Init the list */
        pList polyList = InitList();

        /* Init the menu */
        printf("******** Simple Polynomial Calculator ********\n\n");

        printf("Menu\n");
        printf("1. Make a polynomial.\n");
        printf("2. Output all polynomial(s).\n");
        printf("3. Add two polynomials.\n");
        printf("4. Subtract two polynomials.\n");
        printf("5. Calculate a polynomial (f(x)).\n");
        printf("6. Destroy a polymonial.\n");
        printf("7. Make a polynomial empty.\n");
        printf("8. Change one node of a polynomial.\n");

        printf("\n\nEnter your choice: ");

        
        /* Get the choice */
        int choice = 0;
        scanf("%d", &choice);

        /* check if the input is valid */
        if (!(choice >= 1 && choice <= 8)) {
            printf("Error: Invalid Input!");
            continue;
        }

        /* Do the requested Operation */
        DoOperation(choice, polyList);
    }
    return 0;
}

/* InitList(): generate a poly list 
 * A head pointer is used.
 */

pList InitList(void) {
    pList head = NewListNode();
    pList p = NewListNode();
    head->next = p;
    return head;
}

int DoOperation(int num, pList head) {
    
    switch (num)
    {
        case 1:
            /* Add new polys */
            MakePoly(head);
            break;
        case 2:
            /* Output all polys */
            ShowList(head);
            break;
        case 3:
            /* Add 2 polys */
            DisAndCall(AddPoly, 2, head);
            break;
        case 4:
            /* Sub 2 polys */
            DisAndCall(SubPoly, 2, head);
            break;
        case 5:
            /* Solve One poly */
            DisAndCall(SolvePoly, 1, head);
            break;
        case 6:
            /* Del One poly */
            DelPoly(head);
            break;
        case 7:
            /* Make one poly empty */
            DisAndCall(EmptyPoly, 1, head);
            break;
        case 8:
            /* Make changes to a poly */
            ChangePoly(head);
            break;
        default:
            break;
    }
}