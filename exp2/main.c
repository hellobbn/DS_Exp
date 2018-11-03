/* main.c
 * main functions here
 * mainly used to:
 * 1. process input string
 * 2. Call functions to process it
 */


#include "stack.h"
#include "main.h"
#include "common.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{

    /* Init two stacks */
    pStack leftStack = InitStack();
    pStack rightStack = InitStack();

    /* See if we are going to input */
    if(argc > 1) {
        /* argc > 1, file argument spacified 
         * TODO: Use argument argc[1] to process the file
         */
    }

    /* Start process Input */
    int numLines = 0;
    scanf("%d", &numLines);
    getchar();
    
    int pointerPos = 0;
    int inputMode = 0;
    int commandNum = 0;
    while(commandNum < numLines) {
        if(inputMode) {
            /* In input mode:
             * Push everything to the left stack
             * then Pop them from left to right
             * TODO: Make a new function to do this.
             */
            char c;
            int num = 0;

            while((c = getchar()) != '\n') {
                Push(c, leftStack);
                num ++;
            }
            
            for(int j = num; j > 0; -- j) {
                c = Pop(leftStack);
                Push(c, rightStack);
            }
            inputMode = 0;
        } else {
            /* Not in input mode 
             * In command mode, get the string process it
             */
            char c;
            int len = 0;
            char* input = malloc(STR_LEN * sizeof(char));

            while((c = getchar()) != '\n') {
                input[len++] = c;
            }
            input[len] = '\0';

            commandNum ++;

            /* Process the input */
            int i = GetNum(input, len);

            /* Get the command */
            if(input[0] == 'I') {
                /* Insert */
                inputMode = 1;
            } else if(input[0] == 'G') {
                /* Get */
                PrintRStack(leftStack);
                PrintStack(rightStack);
            } else if(input[0] == 'M') {
                /* Move */
                char tmp;

                int shift = i - pointerPos;
                pointerPos = i;
                if(shift > 0) {
                    /* Shift right */ 
                    for(int k = 0; k < shift; ++ k) {
                        tmp = Pop(rightStack);
                        Push(tmp, leftStack);
                    }
                } else {
                    /* Shift left */
                    shift = -shift;
                    for(int k = 0; k < shift; ++ k) {
                        tmp = Pop(leftStack);
                        Push(tmp, rightStack);
                    }
                }
            } else if(input[0] == 'D') {
                /* Delete */
                for(int k = 0; k < i; ++ k) {
                    Pop(rightStack);
                }
            } else if(input[0] == 'N') {
                char tmp;
                pointerPos ++;
                tmp = Pop(rightStack);
                Push(tmp, leftStack);
            } else if(input[0] == 'P') {
                /* Prev */
                char tmp;
                pointerPos --;
                tmp = Pop(leftStack);
                Push(tmp, rightStack);
            } else if(input[0] == 'R') {
                /* Rotate */
                /* FIXME: NOT RIGHT!!!!! */
                pStack tmpStack = InitStack();
                char tmp;
                for(int k = 0; k < i; ++ k) {
                    tmp = Pop(rightStack);
                    Push(tmp, tmpStack);
                }

                for(int k = 0; k < i; ++ k) {
                    tmp = Pop(tmpStack);
                    Push(tmp, rightStack);
                }
            }
            printf("Pointerpos: %d\n", pointerPos);
            printf("left: ");
            PrintRStack(leftStack);
            printf("\nright: ");
            PrintStack(rightStack);
        }
    }

    return 0;
}

void PrintStack(pStack S) {
    /* S is an empty node */
    pStack p = S->next;
    while(p) {
        putchar(p->c);
        p = p->next;
    }
    putchar('\n');
}

void PrintRStack(pStack S) {
    char* tmp = malloc(STR_LEN * sizeof(char));
    int len = 0;
    pStack p = S->next;
    while(p) {
        tmp[len++] = p->c;
        p = p->next;
    }

    for(int k = len - 1; k >= 0; k --) {
        putchar(tmp[k]);
    }
}

int GetNum(char* s, int len) {
    char* p = s;
    int t = 0;

    int result;

    char c = *p;
    while(c > '9' || c < '0') {
        t ++;
        if(t == len) {
            return 0;
        }
        p += 1;
        c = *p;
    }

    result = atoi(p);
    return result;
}
