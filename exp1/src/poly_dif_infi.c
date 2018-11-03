/* poly_differential.c
 * Used to calculate the poly differential 
 */

#include "main.h"
#include "assistant.h" 
#include "poly_dif_infi.h"
#include "common.h"
#include "del_empty_poly.h"

#include <stdio.h>
#include <stdlib.h>

void PolyDiF(pList p) {
    printf("Printing out available polys :\n");
    ShowList(p, 0);
    
    int choice;
    int n;
    printf("Enter the number of poly: ");
    scanf("%d", &choice);
    printf("Enter the n: ");
    scanf("%d", &n);

    pPoly inPoly = FindPoly(p, choice);
    if(inPoly) {
        /* Maybe we need a new space to save the poly? */
        pPoly newPoly = NewListNode();
        poly_dif(inPoly, newPoly, n);
        PrintPoly(newPoly);

        printf("Do you want to save it? (y/N)");
        flush_stdin();
        char t = 'N';
        scanf("%c", &t);
        if(t == '\n' || t == 'n' || t == 'N') {
            /* Don't save it, destroy the list */
            DestroyPoly(newPoly);
            return;
        } else if(t == 'y' || t == 'Y') {
            /* Save the poly to the end of the poly list */
            while(p->next != NULL) {
                p = p->next;
            }
            p->next = newPoly;
        } else {
            printf("Invalid Input, skipping....\n");
        }
    }
}

/* Do the actual differential*/
void poly_dif(pPoly in, pPoly out, int n) {
    for(pNode p = in->head; p != NULL; p = p->next) {
        /* p is NOT empty -> make a new node */
        pNode tmp = MakeNode();

        tmp->coff = p->coff;
        tmp->freq = p->freq;
        
        for(int i = 0; i < n; ++ i) {
            tmp->coff *= tmp->freq;
            tmp->freq --;
        }
        InsertNode(tmp, out);
    }
}

void PolyInfI(pList p) {
    printf("Printing out available polys: \n");
    ShowList(p, 0);
    printf("Enter the poly number: ");
    int choice;
    scanf("%d", &choice);

    pPoly n = FindPoly(p, choice);
    if(n) {
        pPoly nPoly = NewListNode();
        poly_infi(n, nPoly);
        PrintPoly(nPoly);

        printf("Do you want to save it? (y/N)");
        char save = 'N';
        flush_stdin();
        scanf("%c", &save);
        if(save == 'n' || save == 'N' || save == '\n') {
            DestroyPoly(nPoly);
        } else if(save == 'y' || save == 'Y') {
            while(p->next != NULL) {
                p = p->next;
            }
            p->next = nPoly;
        } else {
            printf("ERROR: Invalide Input, destroy the node...\n");
            DestroyPoly(nPoly);
        }
    }
}

/* Do the actual infl */
void poly_infi(pPoly in, pPoly out) {
    pNode p = in->head;
    while(p != NULL) {
        pNode tmp = MakeNode();
        tmp->freq = p->freq;
        tmp->coff = p->coff;
        if(tmp->freq == -1) {
            /* We met a node whose infl is a ln 
             * not going to change anything in this node.
             * save it to the head and do NOT insert it.
             */
            out->coffLn = tmp->coff;
        } else {
            tmp->freq ++;
            tmp->coff = tmp->coff / tmp->freq;
            InsertNode(tmp, out);
        }
        p = p->next;
    }
}

void PolyDefI(pList p) {
    printf("Printing out available ploys: \n");
    ShowList(p, 0);
    printf("Enter the number: ");
    int choice;
    scanf("%d", &choice);
    pPoly n = FindPoly(p, choice);

    if(n) {
        printf("As it is a definite integral, we need [a, b] to calculate\n");
        double a, b;
        printf("Please Enter a and b: ");
        scanf("%le %le", &a, &b);
        if(a > b) {
            printf("ERROR: a should be less than b!\n");
            return;
        } else if(a == b) {
            printf("0\n");
            return;
        } else {
            pPoly tmpPoly = NewListNode();
            poly_infi(n, tmpPoly);
            if(tmpPoly->coffLn && a <= 0) {
                printf("ERROR: a or b not LEAGAL!\n");
            // }else if(AllowNeg(tmpPoly) && (a <= 0 || b >= 0)) {
            //     printf("ERROR: a or b not allowed!\n");
            } else {
                pNode tmp = tmpPoly->head;
                double result = 0;
                while(tmp != NULL) {
                    double coff = tmp->coff;
                    int freq = tmp->freq;
                    result += coff * (PoW(b, freq) - PoW(a, freq));
                    tmp = tmp->next;
                }
                int sg = 0;             // we have printed something

                /* Conside Ln */
                double lnCoff = tmpPoly->coffLn;
                if(lnCoff) {
                    double inLn = b / a;
                    if(absF(inLn - 1) > 10E-3) {
                        if(absF(lnCoff + 1) < 10E-3) {
                            printf("-");
                        } else if(absF(lnCoff - 1) > 10E-3) {
                            printf("%.2f", lnCoff);
                        }
                        printf("Ln(%.2f)", inLn);
                        sg = 1;
                    }
                }
                if(!sg) {
                    printf("%.2f", result);
                } else {
                    if(result > 0) {
                        printf(" + %.2f", result);
                    } else if(result < 0) {
                        printf("- %.2f", -result);
                    }
                }
                printf("\n");
            }
        }
    }
    printf("Press ENTER to continue......");
    flush_stdin();
    getchar();
}