#include <stdio.h>
#include <stdlib.h>

int startx, starty, endx, endy;

typedef struct node node;
struct node {
    int x;
    int y;
    struct node* dad;
    struct node* next;
};

void answer(node* p)
{
    if (p == NULL) return;
    else {
        answer((*p).dad);
        if(((*p).x != endx) || ((*p).y != endy))
          printf("(%d,%d)->", (*p).x + 1, (*p).y + 1);
        else
          printf("(%d,%d)", (*p).x + 1, (*p).y + 1);
    }
}

int main()
{
    freopen("in5.txt", "r", stdin);
    int n, m, i, j;
    scanf("%d %d", &n, &m);
    int lab[n][m];
    for(i = 0; i < n; ++ i) {
        for(j = 0; j < m; ++ j) {
            scanf("%d", &lab[i][j]);
        }
    }
    node *a, *p;
    scanf("%d %d", &startx, &starty);
    scanf("%d %d", &endx, &endy);
    startx -= 1; starty -= 1;
    endx -= 1; endy -= 1;
    a = malloc(sizeof(struct node));
    (*a).x = startx; (*a).y = starty; (*a).dad = NULL; (*a).next = NULL;
    p = a;
    while (p != NULL) {
        if(((*p).x > 0) && (lab[(*p).x - 1][(*p).y] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*a).next = tmp;
            a = tmp;
            (*tmp).x = (*p).x - 1;
            (*tmp).y = (*p).y;
            (*tmp).dad = p;
            (*tmp).next = NULL;
            if (((*tmp).x == endx) && ((*tmp).y == endy)) {
                    answer(tmp);
                    break;
            }
        }
        if(((*p).y > 0) && (lab[(*p).x][(*p).y - 1] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*a).next = tmp;
            a = tmp;
            (*tmp).x = (*p).x;
            (*tmp).y = (*p).y - 1;
            (*tmp).dad = p;
            (*tmp).next = NULL;
             if (((*tmp).x == endx) && ((*tmp).y == endy)) {
                    answer(tmp);
                    break;
            }
        }
        if(((*p).x < (n-1)) && (lab[(*p).x + 1][(*p).y] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*a).next = tmp;
            a = tmp;
            (*tmp).x = (*p).x + 1;
            (*tmp).y = (*p).y;
            (*tmp).dad = p;
            (*tmp).next = NULL;
             if (((*tmp).x == endx) && ((*tmp).y == endy)) {
                    answer(tmp);
                    break;
            }
        }
        if(((*p).y < (m - 1)) && (lab[(*p).x][(*p).y + 1] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*a).next = tmp;
            a = tmp;
            (*tmp).x = (*p).x;
            (*tmp).y = (*p).y + 1;
            (*tmp).dad = p;
            (*tmp).next = NULL;
             if (((*tmp).x == endx) && ((*tmp).y == endy)) {
                    answer(tmp);
                    break;
            }
        }
        p = (*p).next;
    }
    if (p == NULL) printf("-1");
    return 0;
}