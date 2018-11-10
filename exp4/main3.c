#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main(int argc, char const *argv[])
{
    // Initialize vars
    int row, colum;                 // row and colum
    int startx, starty;             // start point
    int endx, endy;                 // end point
    Queue pointQ = CreateQueue();   // empty queue
  
    scanf("%d %d", &row, &colum);

    int mis[row][colum];            // the graph
    int flag[row][colum];
    for(int i = 0; i < row; ++ i) {
        for(int j = 0; j < colum; ++ j) {
            scanf("%d", &mis[i][j]);
        }
    }

    scanf("%d %d", &startx, &starty);
    scanf("%d %d", &endx, &endy);

    // Init the first element
    pQNode tmp = malloc(sizeof(struct QueueNode));      // tmp points to the node
    tmp->next = NULL;
    tmp->x = startx;
    tmp->y = starty;

    // push it to queue
    Enqueue(tmp, pointQ);

    // mark it
    flag[startx][starty] = 1;
    int queueSize = 1;          // total queue size
    int currPos = 0;            // current pointer position

    // Let's Do the loop!
    while(currPos < queueSize) {
        int currx = tmp->x;
        int curry = tmp->y;
        if(currx != 0 && mis[currx - 1][curry] && !flag[currx - 1][curry]) {
            // up is ok
            pQNode p = malloc(sizeof(struct QueueNode));
            p->x = currx - 1;
            p->y = curry ;
            flag[currx - 1][curry] = 1;
            
            Enqueue(p, pointQ);
            queueSize ++;
        }

        if(currx < row - 1 && mis[currx + 1][curry] && !flag[currx + 1][curry]) {
            // down is ok
            pQNode p = malloc(sizeof(struct QueueNode));
            p->x = currx + 1;
            p->y = curry ;
            flag[currx + 1][curry] = 1;
            Enqueue(p, pointQ);
            queueSize ++;            
        }

        if(curry != 0 && mis[currx][curry - 1] && !flag[currx][curry - 1]) {
            // left is ok
            pQNode p = malloc(sizeof(struct QueueNode));
            p->x = currx;
            p->y = curry - 1;
            flag[currx][curry - 1] = 1;
            Enqueue(p, pointQ);
            queueSize ++;            
        }

        if(curry < colum - 1 && mis[currx][curry + 1] && !flag[currx][curry + 1]) {
            // down is ok
            pQNode p = malloc(sizeof(struct QueueNode));
            p->x = currx;
            p->y = curry + 1;
            flag[currx][curry + 1] = 1;
            Enqueue(p, pointQ);
            queueSize ++;            
        }
    }

    return 0;
}
