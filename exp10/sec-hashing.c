/* Hasing table using Seperate Chaining
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct ChainNode* pChainNode;
typedef struct ChainHead* pChainHead;

struct ChainNode {
    struct ChainNode* next;
    int key;
};
struct ChainHead {
    struct ChainNode* firstNode;
    int chain_len;
    int key;
};

int main(void) {
    int num_size;
    int i;
    scanf("%d", &num_size);

    int key;
    int* key_saver = malloc(sizeof(int) * num_size);

    for(i = 0; i < num_size; ++ i) {
        scanf("%d", &key_saver[i]);
    }


    int mod_set = 0;
    scanf("%d", &mod_set);
    pChainHead* hash_table = malloc(sizeof(pChainHead) * mod_set);
        for(i = 0; i < mod_set; ++ i) {
        hash_table[i] = malloc(sizeof(struct ChainHead));
        hash_table[i]->chain_len = 1;
        hash_table[i]->firstNode = NULL;
    }
    // Process start here
    int mod;
    pChainHead tmp;
    pChainNode p;
    pChainNode new_node;
    for(i = 0; i < num_size; ++ i) {
        key = key_saver[i];
        mod = key % mod_set;

        tmp = hash_table[mod];
        if(tmp->firstNode == NULL) {
            p = malloc(sizeof(struct ChainNode));
            p->key = key;
            p->next = NULL;
            tmp->firstNode = p;
            tmp->chain_len ++;
        } else {
            p = tmp->firstNode;
            while(p->next) {
                p = p->next;
                if(p->key == key) {
                    // duplicated
                    p = NULL;
                    break;
                }
            }
            if(p) {
                new_node = malloc(sizeof(struct ChainNode));
                new_node->key = key;
                new_node->next = NULL;
                p->next = new_node;
                tmp->chain_len ++;
            }
        }
    }

    // Dump the table
    int depth;
    double success_sum = 0;
    double fail_sum = 0;
    int j;
    for(i = 0; i < mod_set; ++ i) {
        tmp = hash_table[i];
        printf("Address %d: \t", i);
        printf("Key: ");
        depth = 0;
        if(tmp->firstNode == NULL) {
            printf("-\t\t");
        } else {
            p = tmp->firstNode;
            while(p){
                printf("%d ", p->key);
                p = p->next;
                depth += 1;
            }
        }
        printf("\n\t\t");
        printf("%s ", "Success");
        depth += 1;
        if(depth == 1) {
            printf("0 ");
        }
        for(j = 1; j < depth; ++ j) {
            printf("%d ", j);
            success_sum += j;
        }

        printf("\t\t\tFail: ");
        printf("%d ", tmp->chain_len);
        fail_sum += tmp->chain_len;
        printf("\n\n");
    }


    printf("Ava: Success: %lf, \t Fail: %lf\n\n", success_sum / num_size, fail_sum / mod_set);
}