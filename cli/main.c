/* main.c
 * Implementing basic user interface and 
 * call other functions to achieve different 
 * operations.
*/

#include <stdio.h>
#include "main.h"

/* Basic Definition of the data structure of a polynomial*/
struct polyNode {
    int coff;
    int freq;
    struct polyNode* next;
};

/* Basic Definition of the data structure of a list*/
struct polyList {
    poly head;
    struct polyList* next;
};

/* Function used in this file */
int DoOperation(int num);

int main(int argc, char const *argv[])
{

    /* The choosing menu should run in a loop. */
    while(1) {
        /* Init the list */

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

    }
    return 0;
}
