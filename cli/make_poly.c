/* Makepoly.c
 * Implement the first function
 */

#include "main.h"
#include "assistant.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void ProcessStr(char* s, pPoly head, int len);
void MakePoly(pList head) {
    /* help messages */
    printf("NOTE: Please use the format 'ax^b' when entering\n");
    printf("For example: \n");
    printf("3x^2 - 4x^3 + 7x^-1\n");
    printf("Press Enter to stop input");

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
        pPoly polytmp = NewListNode();
        // flush_stdin();

        /* As we are adding a new poly, we are making a new list node
         * This list node also serves as the head of the list.
         */
        pPoly lnode = NewListNode();
        p->next = lnode;
        p = p->next;
        printf("Please enter one polynomial: ");
        while((c = getchar()) != '\n') {
            if (c == ' ') {
                continue;
            }
            
            /* if s is full */
            if (len == bufferTotalLen) {
                bufferTotalLen += STR_INCR_STEP;
                char* tmp = realloc(polytmp, bufferTotalLen);

                if(!tmp) {
                    printf("Error: In function %s, buffer is full but realloc() failed",\
                            __func__);
                    exit(1);
                }
                inputStr = tmp;
            }

            inputStr[len++] = c;
        }
#ifdef DEBUG
        printf("%s: inputStr: %s\n", __func__, inputStr);
#endif

        /* Go to process the whole string */
        ProcessStr(inputStr, p, len);
    }
}

void ProcessStr(char* s, pPoly head, int len) {
    
}