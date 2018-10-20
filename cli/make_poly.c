/* Makepoly.c
 * Implement the first function
 */

#include "main.h"
#include "assistant.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void ProcessStr(char* s, pPoly head, int len);
void ProcessExpr(char* s, int len, pNode p);

void MakePoly(pList head) {
    /* help messages */
    printf("NOTE: Please use the format 'ax^b' when entering\n");
    printf("For example: \n");
    printf("3x^2 - 4x^3 + 7x^-1\n");
    printf("Press Enter to stop input\n");

    pList p = head;
    int jobDone = 0;
    
    /* Go to the tail of the poly list */
    while(p->next != NULL) {
        p = p->next;
    }

    /* Main part: make new poly and append
     * When not asked to quit, continue adding polys to list 
     */
    while(!jobDone) {
        int bufferTotalLen = STR_INIT_LEN;
        char c;
        char* inputStr = malloc(bufferTotalLen);
        int len = 0;
        pList polytmp = NewListNode();
        p->next = polytmp;
        p = p->next; 
        flush_stdin();

        /* As we are adding a new poly, we are making a new list node
         * This list node also serves as the head of the list.
         */
        printf("Please enter one polynomial: ");
        while((c = getchar()) != '\n') {
            if (c == ' ') {
                continue;
            }
            
            /* if s is full */
            if (len == bufferTotalLen) {
                ReallocStr(&inputStr, len);
            }

            inputStr[len++] = c;
        }
#ifdef DEBUG_MAKE_POLY
printf("%s: inputStr: %s\n", __func__, inputStr);
#endif

        /* Go to process the whole string when len != 0*/
        if(len) ProcessStr(inputStr, p, len);

#ifdef DEBUG_MAKE_POLY
PrintPoly(p);
#endif
        /* Another poly ? */
        while(1) {
            printf("Do you want to enter another polynomial? (y/N)");
            char choice = 'N';
            char c = getchar();
            if(c != '\n') {
                choice = c;
            }

            if(choice == 'N' || choice == 'n') {
                jobDone = 1;
                break;
            } else if(choice == 'Y' || choice == 'y') {
                jobDone = 0;
                break;
            } else {
                printf("Please enter y or N!\n");
            }
        }
    }
}

void ProcessStr(char* s, pPoly head, int len) {
    int pos = 0;
    int exprStartPos = 0;


    /* When met every opr, we are going to cut and let
     * another function process it
     */
#ifdef DEBUG_MAKE_POLY
printf("In function %s: len = %d\n", __func__, len);
#endif
    while(pos < len) {
        if(IsOpr(*(s+pos)) == 1 || pos == len - 1) {
            /* First of all, we are going to cut here
             * Then we will make a new polyNode to save it
             * We are going to passing them to a new function
             * called ProcessExpr()
             */

#ifdef DEBUG_MAKE_POLY
printf("In function %s: posStart = %d\n pos = %d\n", __func__, exprStartPos, pos);
#endif
            if(pos == exprStartPos) {
                pos ++;
                continue;
            }
            if(*(s + pos - 1) == '^' && pos != len - 1) {
                /* we found a expr whose freq is a - */
                pos ++;
                continue;
            }
            pNode nNode = MakeNode();
            int l = pos - exprStartPos;
            if(pos == len - 1) {
                l += 1;
            }

            ProcessExpr(s + exprStartPos, l, nNode);

            InsertNode(nNode, head);
            exprStartPos = pos;

        }
        pos ++;
    }
}

void ProcessExpr(char* s, int len, pNode p) {
    /* We are assuming the format like this:
     * ax^b
     * where a is a double and b is an int
     * and also note that a and b is not necessarily 
     * required.
     */
#ifdef DEBUG_MAKE_POLY
printf("In function %s: len = %d\n", __func__, len);
for(int i = 0; i < len; ++ i) {
    putchar(s[i]);
}
putchar('\n');
#endif
    int pos = 0;            // records where x is
    int hasB = 0;           // Expr has b
    int hasA = 1;           // Expr has a
    int hasX = 0;           // Expr has x
    int xPos = len;           // Position of x, Default: no x
    while(pos < len) {
        if(*(s + pos) == 'x') {
            hasX = 1;
            xPos = pos;
            if(pos == 0) {
                hasA = 0;
            }
        }else if(*(s + pos) == '^') {
            hasB = 1;
        }
        pos ++;
    }
    int lenA = xPos;
    int lenB = len - xPos - 2;

    // Process a and b
    double a = 1;
    int b = hasX ? 1 : 0;
    if(hasA){
        a = atoF(s, lenA);
    }
    if(hasB){
        b = atoI(s + xPos + 2, lenB);
    }

#ifdef DEBUG_MAKE_POLY
printf("In function %s, a = %lf\t, b = %d\n", __func__, a, b);
#endif
    p->freq = b;
    p->coff = a;
}
