/* main.c
 * program starts here
 */

#include <stdio.h>
#include <stdlib.h>
int minimum = 0;
int row, colum;
int** tmp;
int** way;

void WayCpy(int len, int** in, int** dest);
void TryWay(int** mis, int startx, int starty, int endx, int endy, int len, int** flag);
int main(void) {

    scanf("%d %d", &row, &colum);

    int** mis = malloc(sizeof(int*) * row);
    int** flag = malloc(sizeof(int*) * row);

    tmp = malloc(sizeof(int*) * 2);
    way = malloc(sizeof(int*) * 2);

    for(int i = 0; i < 2; ++ i) {
        tmp[i] = malloc(sizeof(int) * row * colum);
        way[i] = malloc(sizeof(int) * row * colum);
    }

    for(int i = 0; i < row; ++ i) {
        mis[i] = malloc(sizeof(int) * colum);
        flag[i] = malloc(sizeof(int) * colum); 
    }

    for(int i = 0; i < row; ++ i) {
        for(int j = 0; j < colum; ++ j) {
            scanf("%d", &mis[i][j]);
            flag[i][j] = 0;
        }
    } 

    int startx, starty;
    int endx, endy;
    scanf("%d %d", &startx, &starty);
    scanf("%d %d", &endx, &endy);

    minimum = row * colum;
    flag[startx][starty] = 1;
    TryWay(mis, startx - 1, starty - 1, endx - 1, endy - 1, 0, flag);
    
    if(minimum) {
        for(int i = 0; i <= minimum; ++ i) {
            if(i != 0) {
                printf("->");
            }
            printf("(%d, %d)", way[0][i] + 1, way[1][i] + 1);
        }
    }
}

void TryWay(int** mis, int startx, int starty, int endx, int endy, int len, int** flag) {

    tmp[0][len] = startx;
    tmp[1][len] = starty;

    // we have reached the destination
    if(startx == endx && starty == endy) {
        // printf("(%d, %d): Reached!, len = %d\n", startx + 1, starty + 1, len);
        if(len < minimum) {
            minimum = len;
        }
        WayCpy(len + 1, tmp, way);
    }

    // try other ways
    if(startx != 0 && !flag[startx - 1][starty] && mis[startx - 1][starty] != 0) {
        // try go up
        // printf("(%d, %d): Up!\n", startx + 1, starty + 1);
        flag[startx - 1][starty] = 1;
        TryWay(mis, startx - 1, starty, endx, endy, len + 1, flag);
        flag[startx - 1][starty] = 0;
    } 
    
    if(startx != row - 1 && !flag[startx + 1][starty] && mis[startx + 1][starty] != 0) {
        // try go down
        // printf("(%d, %d): Down!\n", startx + 1, starty + 1);
        flag[startx + 1][starty] = 1;
        TryWay(mis, startx + 1, starty, endx, endy, len + 1, flag);
        flag[startx + 1][starty] = 0;
    }

    if(starty != 0 && !flag[startx][starty - 1] && mis[startx][starty - 1] != 0) {
        // try go left
        // printf("(%d, %d): Left!\n", startx + 1, starty + 1);
        flag[startx][starty - 1] = 1;
        TryWay(mis, startx, starty - 1, endx, endy, len + 1, flag);
        flag[startx][starty - 1] = 0;
    }

    if(starty != colum - 1 && !flag[startx][starty + 1] && mis[startx][starty + 1] != 0) {
        // try go right
        // printf("(%d, %d): Right!\n", startx + 1, starty + 1);
        flag[startx][starty + 1] = 1;
        TryWay(mis, startx, starty + 1, endx, endy, len + 1, flag);
        flag[startx][starty + 1] = 0;
    }

    // fuck -> failed 
    if(len == 0) {
        minimum = 0;
        printf("-1");
    }
    // clear the flag
    
    // printf("Going Back!\n");
}

void WayCpy(int len, int** in, int** dest) {
    for(int i = 0; i < len; ++ i) {
        dest[0][i] = in[0][i];
        dest[1][i] = in[1][i];
    }
}

