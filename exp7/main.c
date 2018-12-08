/* Going through a graph 
 * Using data structure: AdjMatrix
 */

/* FLAG */
// #define DEBUG_MAIN
// #define DEBUG_DFS 
// #define DEBUG_BFS

/* Includes */
#include <stdio.h>
#include <stdlib.h>

void SortList(int* list, int len) {
    int i, j;
    int tmp;
    for(i = len - 1; i > 0; -- i) {
        for(j = 0; j < i - 1; ++ j) {
            if(list[j] > list[j + 1]) {
                tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }
}
void DFS(int** adjMatrix, int* Mark, int start, int point_num) {
    int i;
#ifdef DEBUG_DFS
    printf("Check point %d\n", start + 1);
    printf("Mark point %d\n", start + 1);
#endif

    printf("%d", start + 1);

    Mark[start] = 1;
    for(i = 0; i < point_num; ++i) {

#ifdef DEBUG_DFS
    printf("Check point (%d, %d)\n", start + 1, i + 1);
#endif

        if(adjMatrix[start][i]) {
            if(!Mark[i]) {
                printf(" ");
                DFS(adjMatrix, Mark, i, point_num);
            }
        }
    }
    //Mark[start] = 0;
#ifdef DEBUG_DFS
    printf("Unmark point %d\n", start + 1);
    sleep(1);
#endif
    //printf("%d ", i);
}

void BFS(int** adjMatrix, int* map, int start, int point_num ) {
    int queue_pointer = 0;
    int fqueue_end = 1;
    int secqueue_end = 1;
    int i;
    int curr_v = 0;
    int* queue = malloc(sizeof(int) * (point_num + 100));
    int* inqueue = malloc(sizeof(int) * (point_num + 100));
    int sort_begin = 0;
    int sort_len = 0;
    int check = 0;
    for(i = 0; i < point_num + 10; ++ i) {
        queue[i] = 0;
        inqueue[i] = 0;
    }
    queue[0] = start;
    while(queue_pointer != secqueue_end) {
        fqueue_end = secqueue_end;
        while(queue_pointer != fqueue_end) {
            curr_v = queue[queue_pointer];
            map[curr_v] = 1;
            sort_begin = secqueue_end;
            sort_len = 0;
            printf("%d", curr_v + 1);
            if(++ check < point_num) {
                printf(" ");
            } else {
            	queue_pointer = secqueue_end;
            	break;
			}
#ifdef DEBUG_BFS
    printf("Mark %d\n", curr_v + 1);
#endif            
            for(i = 0; i < point_num; ++ i) {
                if(adjMatrix[curr_v][i] && !map[i]) {
                    queue[secqueue_end ++] = i;
                    sort_len ++;
#ifdef DEBUG_BFS
    printf("Enqueue %d\n", i + 1);
#endif
                    map[i] = 1;
                }
            SortList(queue + secqueue_end, sort_len);
            }
            queue_pointer ++;
#ifdef DEBUG_BFS
    printf("finished %d\n", queue[queue_pointer - 1] + 1);
#endif
        }

        /* We are going to sort: from fqueue_end to sec_queue_end 
         * secqueue_end is not included
         */

    }
    free(queue);
    free(inqueue);
}

int main(int argc, char const *argv[])
{
    int point_num, input_num, i, j;
    int a, b, s;
    scanf("%d %d", &point_num, &input_num);

    /* Init Matirx */
    int** adjMatrix = malloc(sizeof(int*) * point_num);
    int* mark = malloc(sizeof(int) * point_num);

    for(i = 0; i < point_num; ++ i) {
        adjMatrix[i] = malloc(sizeof(int) * point_num);

        for(j = 0; j < point_num; ++ j) {
            adjMatrix[i][j] = 0;
        }
    }

    /* Read the Things */
    for(i = 0; i < input_num; ++ i) {
        scanf("%d %d", &a, &b);
        a -= 1;
        b -= 1;
        adjMatrix[a][b] = 1;
        adjMatrix[b][a] = 1;
    }
    scanf("%d", &s);
 
#ifdef DEBUG_MAIN
    printf("===== Dumping Matrix =====\n");
    for(i = 0; i < point_num; ++ i) {
        for(j = 0; j < point_num; ++ j) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("===== DFS START HERE =====\n");
#endif
    for(i = 0; i < point_num; ++ i) {
        mark[i] = 0;
    }
    DFS(adjMatrix, mark, s - 1, point_num);
    printf("\n");
    for(i = 0; i < point_num; ++ i) {
        mark[i] = 0;
    }
#ifdef DEBUG_MAIN
    printf("===== BFS START HERE =====\n");
#endif
    BFS(adjMatrix, mark, s - 1, point_num);
    printf("\n");
    for(i = 0; i < point_num; ++ i) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);
    free(mark);
    return 0;

}
