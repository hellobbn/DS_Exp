/* Makepoly.c
 * Implement the first function
 */

#include "main.h"
#include "assistant.h"
#include "common.h"
#include "make_poly.h"
#include "del_empty_poly.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


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
    int status = 1;
    while(!jobDone) {
        int bufferTotalLen = STR_INIT_LEN;
        char c;
        char* inputStr = malloc(bufferTotalLen);
        int len = 0;
        flush_stdin();
        /* Only create new node when first work succeeded */   
        pList polytmp = NewListNode();
        status = 1;

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
printf("%s: inputStr: %s\n status = %d\n", __func__, inputStr, status);
#endif

        /* Go to process the whole string when len != 0 */
        if(len) status = ProcessStr(inputStr, polytmp, len);

        if(status) {
            printf("\nThe Poly you entered is: \n");
            PrintPoly(polytmp);
            printf("\n");
            p->next = polytmp;
            p = p->next;
        }

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
        free(inputStr);
    }
}

int ProcessStr(char* s, pPoly head, int len) {
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
            if(pos == exprStartPos && IsOpr(*(s+pos))) {
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

            int status = ProcessExpr(s + exprStartPos, l, nNode);
            /* If an error occurred */
            if(status != 1) {
                printf("ERROR: INPUT ERROR\n");
                DestroyPoly(head);
                return 0;
            }

            InsertNode(nNode, head);
            exprStartPos = (*(s + pos) == '-') ? pos : pos+1;

        }
        pos ++;
    }
    return 1;
}

int ProcessExpr(char* s, int len, pNode p) {
    /* We assume the format like this:
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
    int bspos = len;
    char check_c = s[len - 1];
    if(check_c == '-' || check_c == '^') {
        return 0;
    }
    while(pos < len) {
        check_c = *(s + pos);
        if(check_c == 'x') {
            /* has 2 x -> error */
            if(hasX == 1) {
                return 0;
            }

            hasX = 1;
            xPos = pos;
            if(pos == 0) {
                hasA = 0;
            }
        }else if(check_c == '^') {
            hasB = 1;
            bspos = pos;
        } else if(check_c == '.' && pos > bspos) {
            /* double in freq */
            return 0;
        }
        pos ++;
    }
    int lenA = xPos;
    int lenB = len - xPos - 2;

    /* Process a and b */
    double a = 1;
    int b = hasX ? 1 : 0;
    if(hasA){
        /* if a == -1 */ 
        if(lenA == 1 && *(s) == '-') {
            a = -1;
        } else {
            a = atoF(s, lenA);
        }
    }
    if(hasB){
        b = atoI(s + xPos + 2, lenB);
    }

#ifdef DEBUG_MAKE_POLY
printf("In function %s, a = %lf\t, b = %d\n", __func__, a, b);
#endif
    p->freq = b;
    p->coff = a;
    return 1;
}
