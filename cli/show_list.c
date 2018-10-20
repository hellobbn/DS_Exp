#include "main.h"
#include "assistant.h"

#include <stdlib.h>
#include <stdio.h>
/* We are assumming it has a head pointer */
void ShowList(pList list) {
    int cnt = 0;
    pPoly p = list->next;
    while(p != NULL) {
        printf("%d. ", ++cnt);
        PrintPoly(p);
        p = p->next;
    }

    printf("Press ENTER to quit.....");
    flush_stdin();
    getchar();

}