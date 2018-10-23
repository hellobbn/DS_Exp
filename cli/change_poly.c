/* change_poly.c
 * make changes to a poly
 * Functions including:
 * 1. Insert a new node to a poly
 * 2. Delete a existing node in a poly
 * 3. Change the properties of an existing poly
 */

#include "main.h"
#include "assistant.h"
#include "make_poly.h"

#include <stdio.h>
#include <stdlib.h>

void __change_poly(pPoly p);
void change_insert_node(pPoly p);
void change_delete_node(pPoly p);
void change_change_node(pPoly p);


/* First, implement a main menu for changing */
void ChangePoly(pList list) {
    int choice = 0;
    printf("Printing available polys: \n");
    ShowList(list, 0);
    printf("Enter the number of poly you want to change: ");
    scanf("%d", &choice);
    pPoly p = FindPoly(list, choice);
    printf("So it is the poly you want to change: ");
    PrintPoly(p);
    __change_poly(p);
}

/* We are going to find a way to change and start to change it */
void __change_poly(pPoly p) {
    printf("How do you want to do with the polynomial?\n");
    printf("1. Insert new node;\n");
    printf("2. Delete a node;\n");
    printf("3. Change one node's property.\n");
    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            /* Insert a new node */
            change_insert_node(p);
            break;
        case 2:
            /* Delete a node */
            change_delete_node(p);
        case 3:
            /* change a node */
            change_change_node(p);
        default:
            printf("ERROR: Invaild Input!!!\n");
            break;
    }
}

void change_insert_node(pPoly p) {
    printf("Enter the node(s) you want to add: ");
    flush_stdin();
    char c;
    int bufferTotalLen = STR_INIT_LEN;
    char* s = malloc(STR_INIT_LEN);
    int pos = 0;
    while((c = getchar()) != '\n') {
        if(c == ' ') {
            continue;
        }

        if(pos == bufferTotalLen) {
            ReallocStr(&s, pos);
        }
        *(s + pos) = c;
        pos ++;
    }
    ProcessStr(s, p, pos);

    printf("All right, you've changed the poly to: \n");
    PrintPoly(p);
}

void change_delete_node(pPoly p) {
    printf("You are about to spacify the node to make changes to.\n");
    printf("Enter the freq of the node to find it: ");
    int freq = 0;
    scanf("%d", &freq);
    pNode tmp = NULL;
    if(p->head->freq == freq) {
        tmp = p->head;
        p->head = tmp->next;
        free(tmp);
    } else {
        pNode tmpPrev = FindPrevNode(p, freq);
        if(tmpPrev) {
            /* tmp-> prev = freq! so tmp is not empty */
            tmp = tmpPrev->next;
            tmpPrev->next = tmp->next;
            free(tmp);
        }
    }
}

void change_change_node(pPoly p) {
    printf("Enter the freq of the node you want to change: ");
    int freq;
    scanf("%d", &freq);

    pNode n = FindNode(p, freq);
    printf("We are about to change ");
    PrintNode(n);

    double newCoff;
    int newFreq;
    printf("Enter the new Coff here: ");
    scanf("%le", &newCoff);
    printf("Enter the new freq here: ");
    scanf("%d", &newFreq);

    n->freq = newFreq;
    n->coff = newCoff;
}