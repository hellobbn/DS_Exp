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
    // if(argc > 1) {
    //     /* argc > 1, file argument spacified 
    //      * TODO: Use argument argc[1] to process the file
    //      */
    // }

    /* Start process Input */
    int numLines = 0;
    scanf("%d", &numLines);
    char a;
    while((a = getchar()) != EOF && a != '\n');
    
    
    int pointerPos = 0;
    int inputMode = 0;
    int commandNum = 0;
    int inputNum = 0;
    int size = 0;
    while(commandNum < numLines) {
        if(inputMode) {
            /* In input mode:
             * Push everything to the left stack
             * then Pop them from left to right
             * TODO: Make a new function to do this.
             */
            char c;
            int num = 0;

            while((c = getchar()) != '\n' && c != '\r' && c != EOF) {
                if(num == inputNum) {
                    break;
                }
                Push(c, leftStack);
                num ++;
            }
            if(c == '\r') {
                getchar();
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
            
            while((c = getchar()) != '\n' && c != '\r') {
                input[len++] = c;
            }
            if(c == '\r') {
                getchar();
            }
            input[len] = '\0';

            commandNum ++;

            /* Process the input */
            int i = GetNum(input, len);

            /* Get the command */
            if(input[0] == 'I') {
                /* Insert */
                inputMode = 1;
                inputNum = i;
                size += i;
            } else if(input[0] == 'G') {
                /* Get */
                PrintRStack(leftStack, size);
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
                int cnt = 0;
                char t;
                char* tmp = malloc(sizeof(char) * (i + 10));
                for(int k = 0; k < i; ++ k) {
                    t = Pop(rightStack);
                    if(t == 0) {
                        break;
                    }
                    tmp[cnt ++] = t;
                }

                for(int k = 0; k < cnt; ++ k) {
                    Push(tmp[k], rightStack);
                }
            }
            // printf("Pointerpos: %d\n", pointerPos);
            // printf("left: ");
            // PrintRStack(leftStack);
            // printf("\nright: ");
            // PrintStack(rightStack);
            free(input);
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

void PrintRStack(pStack S, int size) {
    char* tmp = malloc(size * sizeof(char));
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
        if(t >= len) {
            return 0;
        }
        p += 1;
        c = *p;
    }

    result = atoi(p);
    return result;
}
