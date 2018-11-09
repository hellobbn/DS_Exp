/* main.c
 * program starts here 
 */

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int isMatch(char left, char right);
int main(void) {
    int times = 0;
    scanf("%d", &times);
    int* record = malloc(sizeof(int) * times);
    for(int i = 0; i < times; ++ i) {
        record[i] = 1;
    }

    getchar();              // clean the '\n'

    for(int i = 0; i < times; ++ i) {
        // printf("\n%d\n", i + 1);
        char c;
        pStack p = InitStack();

        while((c = getchar()) != '@') {
            if(c == '(' || c == '[' || c == '{') {
                // printf("c = %c, Push\n", c);
                Push(c, p);
            } else if(c == ')' || c == '}' || c == ']') {
                // printf("c = %c, Pop\n", c);
                char another = Pop(p);
                if(another == 0) {
                    // printf("another is 0 -> NO!\n");
                    record[i] = 0;
                } else {
                    int tmp = isMatch(another, c);
                    if(tmp == 0) {
                        record[i] = 0;
                    }
                }
            }
        }
        if(p->next != NULL) {
            record[i] = 0;
        }
    }

    for(int i = 0; i < times; ++ i) {
        if(record[i] == 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int isMatch(char left, char right) {
    if(left == '(')
        return right == ')';
    else if(left == '[')
        return right == ']';
    else if(left == '{')
        return right == '}';

    return 0;
}