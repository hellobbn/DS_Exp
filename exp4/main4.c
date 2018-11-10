#include <stdio.h>
#include <stdlib.h>

int startx, starty, endx, endy, luofan = 0;

typedef struct node node;
struct node {
    int x;
    int y;
    struct node* dad;
    struct node* next;
};

void answera1(node* p)
{
    if (p == NULL) return;
    else {
        answera1((*p).dad);
        printf("(%d,%d)->", (*p).x + 1, (*p).y + 1);
    }
}

void answerb1(node* p)
{
    if (p == NULL) return;
    else {
        if (((*p).x != endx) || ((*p).y != endy)){
        printf("(%d,%d)->", (*p).x + 1, (*p).y + 1);
        }
        else
            printf("(%d,%d)", (*p).x + 1, (*p).y + 1);
        answerb1((*p).dad);
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
    node *a, *p1, *b, *p2, *aflag, *bflag;
    aflag = malloc(sizeof(node) * n);
    for (i = 0; i < n; i++){
        aflag[i] = malloc(sizeof(node*) * m);
        for (j = 0; j < m; j++) aflag[i][j] = NULL;
    }
    bflag = malloc(sizeof(node) * n);
    for (i = 0; i < n; i++){
        bflag[i] = malloc(sizeof(node*) * m);
        for (j = 0; j < m; j++) bflag[i][j] = NULL;
    }
    scanf("%d %d", &startx, &starty);
    scanf("%d %d", &endx, &endy);
    startx -= 1; starty -= 1;
    endx -= 1; endy -= 1;
    a = malloc(sizeof(struct node));
    b = malloc(sizeof(struct node));
    (*a).x = startx; (*a).y = starty; (*a).dad = NULL; (*a).next = NULL;
    (*b).x = endx; (*b).y = endy; (*b).dad = NULL; (*b).next = NULL;
    p1 = a; p2 = b;
    aflag[startx][starty] = p1;
    bflag[endx][endy] = p2;
    while ((p1 != NULL) || (p2 != NULL)) {
      //printf("p1 = (%d, %d) ", (*p1).x, (*p1).y);
      //printf("p2 = (%d, %d)\n", (*p2).x, (*p2).y);
      if (p1 != NULL) {
        if(((*p1).x > 0) && (lab[(*p1).x - 1][(*p1).y] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*a).next = tmp;
            a = tmp;
            (*tmp).x = (*p1).x - 1;
            (*tmp).y = (*p1).y;
            (*tmp).dad = p1;
            (*tmp).next = NULL;

            //printf("A%d %d\n", (*tmp).x, (*tmp).y);

            if (aflag[(*a).x][(*a).y] == NULL) aflag[(*a).x][(*a).y] = a;
            if (bflag[(*a).x][(*a).y] != NULL) {
                    answera1(tmp);
                    answerb1((*bflag[(*a).x][(*a).y]).dad);
                    luofan = 1;
                    break;
            }
        }
        if(((*p1).y > 0) && (lab[(*p1).x][(*p1).y - 1] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*a).next = tmp;
            a = tmp;
            (*tmp).x = (*p1).x;
            (*tmp).y = (*p1).y - 1;
            (*tmp).dad = p1;
            (*tmp).next = NULL;

            //printf("A%d %d\n", (*tmp).x, (*tmp).y);

            if (aflag[(*a).x][(*a).y] == NULL) aflag[(*a).x][(*a).y] = a;
            if (bflag[(*a).x][(*a).y] != NULL) {
                    answera1(tmp);
                    answerb1((*bflag[(*a).x][(*a).y]).dad);
                    luofan = 1;
                    break;
            }
        }
        if(((*p1).x < (n-1)) && (lab[(*p1).x + 1][(*p1).y] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*a).next = tmp;
            a = tmp;
            (*tmp).x = (*p1).x + 1;
            (*tmp).y = (*p1).y;
            (*tmp).dad = p1;
            (*tmp).next = NULL;

           // printf("A%d %d\n", (*tmp).x, (*tmp).y);

            if (aflag[(*a).x][(*a).y] == NULL) aflag[(*a).x][(*a).y] = a;
            if (bflag[(*a).x][(*a).y] != NULL) {
                    answera1(tmp);
                    answerb1((*bflag[(*a).x][(*a).y]).dad);
                    luofan = 1;
                    break;
            }
        }
        if(((*p1).y < (m - 1)) && (lab[(*p1).x][(*p1).y + 1] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*a).next = tmp;
            a = tmp;
            (*tmp).x = (*p1).x;
            (*tmp).y = (*p1).y + 1;
            (*tmp).dad = p1;
            (*tmp).next = NULL;

            //printf("A%d %d\n", (*tmp).x, (*tmp).y);

            if (aflag[(*a).x][(*a).y] == NULL) aflag[(*a).x][(*a).y] = a;
            if (bflag[(*a).x][(*a).y] != NULL) {
                    answera1(tmp);
                    answerb1((*bflag[(*a).x][(*a).y]).dad);
                    luofan = 1;
                    break;
        }
        }
        p1 = (*p1).next;
      }

       if (p2 != NULL) {
        if(((*p2).x > 0) && (lab[(*p2).x - 1][(*p2).y] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*b).next = tmp;
            b = tmp;
            (*tmp).x = (*p2).x - 1;
            (*tmp).y = (*p2).y;
            (*tmp).dad = p2;
            (*tmp).next = NULL;

            //printf("B%d %d\n", (*tmp).x, (*tmp).y);

            if (bflag[(*b).x][(*b).y] == NULL) bflag[(*b).x][(*b).y] = b;
            if (aflag[(*b).x][(*b).y] != NULL) {
                    answera1(aflag[(*b).x][(*b).y]);
                    answerb1((*b).dad);
                    luofan = 1;
                    break;
            }
        }
        if(((*p2).y > 0) && (lab[(*p2).x][(*p2).y - 1] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*b).next = tmp;
            b = tmp;
            (*tmp).x = (*p2).x;
            (*tmp).y = (*p2).y - 1;
            (*tmp).dad = p2;
            (*tmp).next = NULL;

            //printf("B%d %d\n", (*tmp).x, (*tmp).y);

            if (bflag[(*b).x][(*b).y] == NULL) bflag[(*b).x][(*b).y] = b;
            if (aflag[(*b).x][(*b).y] != NULL) {
                    answera1(aflag[(*b).x][(*b).y]);
                    answerb1((*b).dad);
                    luofan = 1;
                    break;
            }
        }
        if(((*p2).x < (n-1)) && (lab[(*p2).x + 1][(*p2).y] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*b).next = tmp;
            b = tmp;
            (*tmp).x = (*p2).x + 1;
            (*tmp).y = (*p2).y;
            (*tmp).dad = p2;
            (*tmp).next = NULL;

            //printf("B%d %d\n", (*tmp).x, (*tmp).y);

            if (bflag[(*b).x][(*b).y] == NULL) bflag[(*b).x][(*b).y] = b;
            if (aflag[(*b).x][(*b).y] != NULL) {
                    answera1(aflag[(*b).x][(*b).y]);
                    answerb1((*b).dad);
                    luofan = 1;
                    break;
            }
        }
        if(((*p2).y < (m - 1)) && (lab[(*p2).x][(*p2).y + 1] != 0)){
            node *tmp;
            tmp = malloc(sizeof(struct node));
            (*b).next = tmp;
            b = tmp;
            (*tmp).x = (*p2).x;
            (*tmp).y = (*p2).y + 1;
            (*tmp).dad = p2;
            (*tmp).next = NULL;

            //printf("B%d %d\n", (*tmp).x, (*tmp).y);

            if (bflag[(*b).x][(*b).y] == NULL) bflag[(*b).x][(*b).y] = b;
            if (aflag[(*b).x][(*b).y] != NULL) {
                    answera1(aflag[(*b).x][(*b).y]);
                    answerb1((*b).dad);
                    luofan = 1;
                    break;
            }
        }
        p2 = (*p2).next;
       }
    }
    if (luofan == 0) printf("-1");
    return 0;
}