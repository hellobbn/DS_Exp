/* main.c
 * main function
 * program entry
 */
/* TODO: 
 * 1. output averagetime
 * 2. average_time = 0
 */
// #define DEBUG
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

person CheckQueue(int total, Queue Q);
void IncrTime(Queue Q);
int FindInQueue(Queue Q, int total);

int main(void) {

    // freopen("/Users/bbn/Desktop/data/t4/in5.txt", "r", stdin);
    /* Init variables */
    int people_num, total, close_time, average_time;        // global control 
    // int* eve_time;                  // every person's waiting time
    int people = 0;                 // how many people has in?
    int curr_time = 0;              // the time
    int first_open = 1;             // first window status
    int second_open = 0;            // second window status
    int process_time = 0;           // process time
    int process_zero = 0;

    /* get variables */
    scanf("%d %d %d %d", &people_num, &total, &close_time, &average_time);

    
    if(average_time == 0) {
        average_time = 1;
        process_zero = 1;
    }

    /* Init queues */
    Queue firstQueue = CreateQueue();         // first queue
    Queue secondQueue = CreateQueue();        // second queue

    /* it should be an array */
    person* allPeople = malloc(sizeof(struct aPerson) * people_num);

    /* Init avetime */
    int all_time = 0;

    /* Read all people's property into the queue */ 
    for(int i = 0; i < people_num; ++ i) {
        int money;
        int enter_time;

        scanf("%d %d", &money, &enter_time);
        person tmp = malloc(sizeof(struct aPerson));
        tmp->deps_money = money;
        tmp->time = enter_time;
        tmp->num = i + 1;
        tmp->end = close_time;
        tmp->next = NULL;

        allPeople[i] = tmp;
    }

    /* While the bank is not closed -> continue to check people */
    while(curr_time < close_time || (process_time != 0 && process_time < average_time)) {
        // printf("curr_time = %d\n", curr_time);
        if(people < people_num) {
            person tmp = allPeople[people];
            if(tmp->time == curr_time) {
#ifdef DEBUG
                printf("In time: %d En people %d to first queue.\n", curr_time, people + 1);
#endif
                Enqueue(tmp, firstQueue);
                people ++;
            }
        }

        /* Increase the waiting time */
        curr_time++;
        // IncrTime(firstQueue);
        // IncrTime(secondQueue);

        /* Process the first queue 
         * TODO: make this a function
         */
        if(first_open) {
            person top = Front(firstQueue);

            /* Check if met */
            if(top) {
                if(top->deps_money + total < 0) {
                    /* NOT MET! move to second queue */
                    process_time = 0;
                    FrontAndDequeue(firstQueue);
                    Enqueue(top, secondQueue);
                    curr_time --;
#ifdef DEBUG
                    printf("In time %d, person %d no money, go to queue 2\n", curr_time, top->num);
#endif
                    continue;
                }

                /* Process the man! */
                process_time ++;

                /* Check if it is ok */
                if(process_time >= average_time) {
                    int top_money = top->deps_money;   
                    
                    if(top_money > 0) {
                        /* 1. finish the operation */
                        total += top_money;
                        top->end = curr_time;
                        top->end -= average_time;
                        FrontAndDequeue(firstQueue);
                        process_time = 0;
#ifdef DEBUG
                        printf("In time %d, person %d out queue 1, depo: %d,money left: %d, check queue 2\n", curr_time, top->num, top->deps_money,total);
#endif
                        /* 2. check the second queue */
                        int found = FindInQueue(secondQueue, total);
                        if(found) {
                            /* Go to the second queue */
#ifdef CONFIG                            
                            printf("Find in queue 2\n");
#endif
                            second_open = 1;
                            first_open = 0;
                        }
                    } else if(top_money + total >= 0) {
                        /* Have a nice day! */

                        total += top_money;
                        top->end = curr_time;
                        top->end -= average_time;
                        FrontAndDequeue(firstQueue);
#ifdef DEBUG
                        printf("In time %d, person %d out queue 1, depo: %d,money left: %d\n", curr_time, top->num, top->deps_money,total);
#endif
                        process_time = 0;
                    }
                }
            }
        } else if(second_open) {
#ifdef DEBUG
            printf("In time %d, Queue2 start.\n", curr_time);
#endif
            /* The second top is ok */
            person top = Front(secondQueue);

            /* Process the man! */
            process_time ++;

            if(top) {
                if(process_time >= average_time) {
                    /* OK! Byebye! */
                    total += top->deps_money;
                    top->end = curr_time;
                    top->end -= average_time;
                    if(process_zero) {
                        top->end --;
                    }
                    FrontAndDequeue(secondQueue);
                    process_time = 0;
#ifdef DEBUG
                    printf("In time %d, person %d out queue 2, money left: %d, check queue 2\n", curr_time, top->num, total);
#endif
                    /* Check again */
                    int found = FindInQueue(secondQueue, total);
                    if(!found) {
                        first_open = 1;
                        second_open = 0;
#ifdef DEBUG
                        printf("not found in queue 2\n");
#endif
                    }
                }
            }
        }
        // printf("person2, waiting time: %d\n", allPeople->arr[1]->waiting_time);
        /* Update curr_time */
        // curr_time ++;

    }

    /* Print out all */
    for(int i = 0; i < people_num; ++ i) {
        all_time += allPeople[i]->end - allPeople[i]->time;
        printf("%d\n", allPeople[i]->end - allPeople[i]->time);
    }
    printf("%d", all_time/people_num);
}

// void IncrTime(Queue Q) {
//     int size = Q->size;
//     person fnt = Q->front;
//     int cnt = 0;
//     while(cnt < size) {
//         fnt->waiting_time ++;
//         fnt = fnt->next;
//         cnt ++;
//     }
// }

int FindInQueue(Queue Q, int total) {
    int s = Q->size;
    person fnt = Q->front;
    int cnt = 0;

    while(cnt < s) {
        if(fnt->deps_money + total >= 0) {
            return 1;
        } else {
            Enqueue(FrontAndDequeue(Q), Q);
            fnt = Front(Q);
            cnt ++;
        }
    }
    return 0;
}
