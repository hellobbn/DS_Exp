#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
    int number, distance;
    struct node* next;
};

void free_point(node* v) {
    if(v == NULL) {
        return;
    } else {
        free_point(v->next);
        free(v->next);
    }
}
int main()
{
    int n, m, x, y, i, j, k, p, start, destin;
    node** vert;
    node* q;
    node* tmp;
    int* dis; 
	int* tag;
    scanf("%d %d", &n, &m);
    vert = malloc(sizeof(node *) * n);
    for (i = 0; i < n; i++) vert[i] = NULL;
    for (i = 0; i < m; i++)
    {
        scanf("%d %d %d", &x, &y, &k);
        x -= 1; y -= 1;
        if (vert[x] == NULL)
        {
            tmp = malloc(sizeof(node));
            if(!tmp) {
            	printf("ERROR\n");
            	return 1;
			}
            tmp->number = y;
            tmp->distance = k;
            tmp->next = NULL;
            vert[x] = tmp;
        }
        else
        {
            q = vert[x];
            while (q->next != NULL) q = q->next;
            tmp = malloc(sizeof(node));
            if(!tmp) {
            	printf("ERROR\n");
            	return 1;
			}
            tmp->number = y;
            tmp->distance = k;
            tmp->next = NULL;
            q->next = tmp;
        }
        if (vert[y] == NULL)
        {
            tmp = malloc(sizeof(node));
            if(!tmp) {
            	printf("ERROR\n");
            	return 1;
			}
            tmp->number = x;
            tmp->distance = k;
            tmp->next = NULL;
            vert[y] = tmp;
        }
        else
        {
            q = vert[y];
            while (q->next != NULL) q = q->next;
            tmp = malloc(sizeof(node));
            if(!tmp) {
            	printf("ERROR\n");
            	return 1;
			}
            tmp->number = x;
            tmp->distance = k;
            tmp->next = NULL;
            q->next = tmp;
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
    for(i = 0; i < n; ++ i) {

    }
    free(vert);
    free(dis);
    free(tag);
    return 0;
}
