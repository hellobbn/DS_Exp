/* Use Prim's Algorithm */

#include <stdio.h>
#include <stdlib.h>

typedef struct eNode* pENode;
typedef struct vNode* pVNode;

struct eNode {
    int weight;
    struct eNode* next;
    struct vNode* connect_to;
};

struct vNode {
    struct eNode* first;
    int no;
    int minWeight;
    int minV;
};

void UpdateVertix(pVNode v, int* map) {
    pENode tmpe = v->first;
    int minW = 20000;
    int minV = -1;

    while(tmpe != NULL) {
        if(!map[tmpe->connect_to->no]) {
            if(tmpe->weight < minW) {
                minW = tmpe->weight;
                minV = tmpe->connect_to->no;
            }
        }
        tmpe = tmpe->next;
    }

    v->minWeight = minW;
    v->minV = minV;
}
int main(int argc, char const *argv[])
{
    int v_num, e_num;
    int i;
    int a, b, w;
    int total = 0;

    scanf("%d %d", &v_num, &e_num);

    pVNode* vList = malloc(sizeof(pVNode) * v_num);

    for(i = 0; i < v_num; ++ i) {
        vList[i] = malloc(sizeof(struct vNode));
        vList[i]->no = i;
        vList[i]->first = NULL;
        vList[i]->minWeight = -1;
        vList[i]->minV = i;
    }

    for(i = 0; i < e_num; ++ i) {
        scanf("%d%d%d", &a, &b, &w);
        pVNode x = vList[a - 1];
        pVNode y = vList[b - 1];

        pENode from_x_to_y = malloc(sizeof(struct eNode));
        pENode from_y_to_x = malloc(sizeof(struct eNode));

        from_x_to_y->connect_to = y;
        from_x_to_y->next = NULL;
        from_x_to_y->weight = w;

        from_y_to_x->connect_to = x;
        from_y_to_x->next = NULL;
        from_y_to_x->weight = w;

        pENode tmp = NULL;

        if(x->first == NULL) {
            x->first = from_x_to_y;
        } else {
            tmp = x->first;
            while(tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = from_x_to_y;
        }

        if(y->first == NULL) {
            y->first = from_y_to_x;
        } else {
            tmp = y->first;
            while(tmp->next != NULL) {
                tmp = tmp->next;
            }
            tmp->next = from_y_to_x;
        }

        if(x->minWeight == -1 || x->minWeight > w) {
            x->minWeight = w;
            x->minV = y->no;
        }

        if(y->minWeight == -1 || y->minWeight > w) {
            y->minWeight = w;
            y->minV = x->no;
        }
    }

    // Prim Start here
    int* markV = malloc(sizeof(int) * v_num);
    int* mapV = malloc(sizeof(int) * v_num);

    for(i = 0; i < v_num; ++ i) {
        markV[i] = 0;
        mapV[i] = 0;
    }

    markV[0] = 0;           // Mark the first point
    mapV[0] = 1;

    int foundPoint = 1;

    while(foundPoint < v_num) {
        int leastWeight = 200000;           // Set as infinity
        int leastVNum = -1;
        int needUpdate = -1;
        int needUpdatean = -1;

        int found = 0;
        pVNode tmpv;
        for(i = 0; i < foundPoint; ++ i) {
            tmpv = vList[markV[i]];
            if(tmpv->minWeight < leastWeight) {
                leastWeight = tmpv->minWeight;
                leastVNum = tmpv->minV;
                needUpdate = leastVNum;
                
                found = 1;
            }
        }

        // Now we have found the least vertex
        if(found){
            markV[foundPoint ++] = leastVNum;
            mapV[leastVNum] = 1;
            found = 0;
            // Update the required thing
            tmpv = vList[needUpdate];
            pENode e = tmpv->first;

            while(e != NULL) {
                UpdateVertix(e->connect_to, mapV);
                e = e->next;
            }
            // printf("Found Point %d has least Weight %d\n", leastVNum + 1, leastWeight);
        } else {
            break;
        }
        total += leastWeight;
    } 

    printf("%d\n", total);
    return 0;
}
