/* Kruscal */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define DEBUG_S1

typedef struct ENode ENode;
typedef ENode* pENode;
typedef struct VNode VNode;
typedef VNode* pVNode;

struct ENode {
    int a;
    int b;
    int weight;
    pENode* nextarc;
};
 
struct VNode {
    pENode* firstarc;
    int num;
};

int has_route(int v1, int v2, pVNode* g);
void add_e(int v, pVNode* g, pENode e) {
    pVNode tmp = g[v];
    pENode p = NULL;
    if(tmp->firstarc) {
        for(p = tmp->firstarc; p->nextarc; p = p->nextarc);
        p->nextarc = e;
    } else {
        tmp->firstarc = e;
    }
}
int my_cmp(const void* a, const void* b) {
    pENode p = *(pENode *)a;
    pENode q = *(pENode *)b;

    if(p->weight > q->weight) {
        return 1;
    } else if(p->weight == q->weight) {
        return 0;
    } else {
        return -1;
    }
}
void Kruscal(pENode* EList, int v_num, int e_num) {
    int i, j;
    int result = 0;
    pENode tmp;

    /* sort the list */
#ifdef DEBUG_S1
    printf("===== SORT START HERE =====");
#endif

    qsort(EList, e_num, sizeof(pENode), my_cmp);

#ifdef DEBUG_S1
    printf("===== SORT END HERE =====\n ===== PRINT START HERE =====\n");
    for(i = 0; i < e_num; ++ i) {
        printf("%d \t", EList[i]->weight);
    }
    printf("\n===== PRINT END HERE =====");
#endif

    /* Init an empty graph */
    pVNode* vertices = malloc(v_num * sizeof(pVNode));
    for(i = 0; i < v_num; ++ i) {
        vertices[i]->firstarc = NULL;
        vertices[i]->num = i;
    }

    /* Find the e */
    int point;
    int p, q;
    for(point = 0; point < e_num; ++ point) {
        pENode e = EList[point];
        p = e->a;
        q = e->b;
        if(has_route(p, q, vertices)) {
            point ++;
            continue;
        } else {
            pENode en = NULL;
            add_e(p, e, vertices);
            add_e(q, e, vertices);
            result += e->weight;
        }
    }

}

int main(int argc, char const *argv[])
{
    int v_num, e_num;
    int i;
    int a, b, w;
    scanf("%d %d", &v_num, &e_num);

    pENode* EList = malloc(sizeof(pENode) * e_num);
    for(i = 0; i < e_num; ++ i) {
        EList[i] = malloc(sizeof(struct ENode));
        pENode e = EList[i];
        scanf("%d %d %d", &a, &b, &w);
        e->a = a;
        e->b = b;
        e->weight = w;
    }

    Kruscal(EList, v_num, e_num);
    return 0;
}
