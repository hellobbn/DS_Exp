/* expr.c
 * Calculate Expressions
 */

#include "main.h"
#include "assistant.h"
#include "common.h"
#include "stack.h"
#include "nodestack.h"

#include <stdio.h>
#include <stdlib.h>

pPoly DoOpr(pPoly a, pPoly b, char opr);
void PolyExpr(pList list) {
    /* Print available polys */
    printf("Print available polys: \n");
    ShowList(list, 0);

    printf("Enter the expression: ");
    flush_stdin();
    int len = 0;
    char c;
    char num[STR_INIT_LEN];

    pStack oprStack = CreateStack();
    pnStack ndStack = CreatenStack();
    while((c = getchar()) != '\n') {
        if(c == ' ') continue;
        if(IsOpr(c)) {
            char t;
            len = 0;
            while(1) {
                t = ShowElem(oprStack);
                if(t == 0) {
                    Push(c, oprStack);
                    break;
                } else if(c == ')' && t =='(') {
                    Pop(oprStack);
                    break;
                } else if(t == '(' && c == '(') {
                    Push(c, oprStack);
                    break;
                } else if (CmpOpr(t, c) == 1) {
                    pPoly x = nPop(ndStack);
                    pPoly y = nPop(ndStack);
                    char opr = Pop(oprStack);
                    pPoly out = DoOpr(y, x, opr);
                    nPush(out, ndStack);
                } else {
                    Push(c, oprStack);
                    break;
                }
            }
        } else {
            num[len++] = c;
            int i = atoI(num, len);
            pPoly out = FindPoly(list, i);
            if(out) {
                nPush(out, ndStack);
            }
        }
    }
    /* Empty it */
    char t;
    while((t = ShowElem(oprStack)) != 0) {
        pPoly x = nPop(ndStack);
        pPoly y = nPop(ndStack);
        char opr = Pop(oprStack);
        pPoly out = DoOpr(y, x, opr);
        nPush(out, ndStack);
    }
    pPoly final = nPop(ndStack);
    PrintPoly(final);
}

pPoly DoOpr(pPoly a, pPoly b, char opr) {
    pPoly p;
    switch(opr) {
        case '+' :
            p = AddPoly(a, b);
            break;
        case '-' :
            p = SubPoly(a, b);
            break;
        case '*':
            p = PolyMultip(a, b);
            break;
        case '/':
            p = PolyDiv(a, b);
            break;
        default:
            p = NULL;
            break;
    }
    return p;
}