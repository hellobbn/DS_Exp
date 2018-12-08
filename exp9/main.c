#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
    int number, distance;
    struct node* next;
};

int main()
{
    int n, m, x, y, i, j, k, p, start, destin;
    node ** vert;
    node * q;
    int * dis; int * tag;
    scanf("%d %d", &n, &m);
    vert = malloc(sizeof(node *) * n);
    for (i = 0; i < n; i++) vert[i] = NULL;
    for (i = 0; i < m; i++)
    {
        scanf("%d %d %d", &x, &y, &k);
        x -= 1; y -= 1;
        if (vert[x] == NULL)
        {
            vert[x] = malloc(sizeof(node*));
            vert[x]->number = y;
            vert[x]->distance = k;
            vert[x]->next = NULL;
        }
        else
        {
            q = vert[x];
            while (q->next != NULL) q = q->next;
            q->next = malloc(sizeof(node*));
            q->next->number = y;
            q->next->distance = k;
            q->next->next = NULL;
        }
        if (vert[y] == NULL)
        {
            vert[y] = malloc(sizeof(node*));
            vert[y]->number = x;
            vert[y]->distance = k;
            vert[y]->next = NULL;
        }
        else
        {
            q = vert[y];
            while (q->next != NULL) q = q->next;
            q->next = malloc(sizeof(node*));
            q->next->number = x;
            q->next->distance = k;
            q->next->next = NULL;
        }
    }

    scanf("%d %d", &start, &destin);
    start -= 1; destin -= 1;
    dis = malloc(sizeof(int) * n);
    tag = malloc(sizeof(int) * n);
    for (i = 0; i < n; i++) {dis[i] = -1; tag[i] = 0;}
    dis[start] = 0; tag[start] = 1;
    q = vert[start];
    while (q != NULL)
    {
        dis[q->number] = q->distance;
        q = q->next;
    }
    for (i = 0; i < (n - 1); i++)
    {
        p = -1; k = 0;
        for (j = 0; j < n; j++)
        {
            if ((tag[j] == 0)&&(dis[j] != -1))
            {
                if ((p == -1)||(dis[j] < p))
                {
                    p = dis[j]; k = j;
                }
            }
        }
        tag[k] = 1;
        q = vert[k];
        while (q != NULL)
        {
            if ((dis[q->number] == -1)||(q->distance + dis[k] < dis[q->number]))
            {
                dis[q->number] = q->distance + dis[k];
            }
            q = q->next;
        }
    }
    printf("%d", dis[destin]);
    return 0;
}
