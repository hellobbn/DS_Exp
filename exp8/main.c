/* Kruscal */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	if(parent[v] == v) {
		return v;
	} else {
		parent[v] = Find(parent[v], parent);
		return parent[v];
	}
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
    int i, point, p, q;
    int result = 0;
    pENode e;

    qsort(EList, e_num, sizeof(pENode), my_cmp);

    int* parent = malloc(sizeof(int) * v_num);
    for( i = 0; i < v_num; ++ i) {
        parent[i] = i;
    }
    /* Find the e */

    for(point = 0; point < e_num; ++ point) {
        e = EList[point];
        p = e->a;
        q = e->b;
        int pv1 = Find(p, parent);
        int pv2 = Find(q, parent);

        if(pv1 != pv2) {
            parent[pv2] = pv1;
            result += e->weight;
    	}
    }
    printf("%d", result);
    free(parent);
}

int main(void) {
   // freopen("C:\\Users\\Chen LF\\test\\data\\t2\\in9.txt", "r", stdin);
    int v_num, e_num;
    int i;
    int a, b, w;
    pENode e;
    scanf("%d %d", &v_num, &e_num);

    pENode* EList = malloc(sizeof(pENode) * e_num);
    for(i = 0; i < e_num; ++ i) {
        EList[i] = malloc(sizeof(struct ENode));
        e = EList[i];
        scanf("%d %d %d", &a, &b, &w);
        e->a = a - 1;
        e->b = b - 1;
        e->weight = w;
    }
    Kruscal(EList, v_num, e_num);
    
    free(EList);
    return 0;
}
