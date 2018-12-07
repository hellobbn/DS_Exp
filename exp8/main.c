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
};
 
struct VNode {
    pENode firstarc;
    int num;
};

int Find(int v, int* parent) {
    while(v != parent[v]) {
        v = parent[v];
    }
    return v;
}

int my_cmp(const void* a, const void* b) {
    pENode p = *(pENode *)a;
    pENode q = *(pENode *)b;

    int wp = p->weight;
    int wq = q->weight;
    if(wp > wq) {
        return 1;
    } else if(wp == wq) {
        return 0;
    } else {
        return -1;
    }
}

void Kruscal(pENode* EList, int v_num, int e_num) {
    int i;
    int result = 0;

    /* sort the list */
#ifdef DEBUG_S1
    printf("===== SORT START HERE =====\n");
#endif

    qsort(EList, e_num, sizeof(pENode), my_cmp);

#ifdef DEBUG_S1
    printf("===== SORT END HERE =====\n ===== PRINT START HERE =====\n");
    for(i = 0; i < e_num; ++ i) {
        printf("%d \t", EList[i]->weight);
    }
    printf("\n===== PRINT END HERE =====\n");
#endif


    int* parent = malloc(sizeof(int) * v_num);
    for( i = 0; i < v_num; ++ i) {
        parent[i] = i;
    }
    /* Find the e */
    int point;
    int p, q;
    for(point = 0; point < e_num; ++ point) {
        pENode e = EList[point];
        p = e->a;
        q = e->b;
        int pv1 = Find(p, parent);
        int pv2 = Find(q, parent);

#ifdef DEBUG_S1
    printf("point %d, from %d to %d, weight = %d, parent[%d] = %d, parent[%d] = %d\n", point, p + 1, q + 1, e->weight ,p + 1, pv1 + 1, q + 1, pv2 + 1);
#endif

        if(pv1 != pv2) {
            parent[pv2] = pv1;
#ifdef DEBUG_S1
    printf("parent[%d] set to %d, parent[%d] set to %d\n", p + 1, parent[p] + 1, q + 1, parent[q] + 1);
#endif
            result += e->weight;
        }
    }
    printf("%d", result);
    free(parent);
}

int main(int argc, char const *argv[]) {
    int v_num, e_num;
    int i;
    int a, b, w;
    scanf("%d %d", &v_num, &e_num);

    pENode* EList = malloc(sizeof(pENode) * e_num);
    for(i = 0; i < e_num; ++ i) {
        EList[i] = malloc(sizeof(struct ENode));
        pENode e = EList[i];
        scanf("%d %d %d", &a, &b, &w);
        e->a = a - 1;
        e->b = b - 1;
        e->weight = w;
    }
    Kruscal(EList, v_num, e_num);
    
    free(EList);
    return 0;
}
