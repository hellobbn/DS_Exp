/* main.c
 * main function
 * program entry
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

person CheckQueue(int total, Queue Q);
void IncrTime(Queue Q);

int main(void) {

    // fopen("/Users/bbn/Desktop/data/t4/in3.txt", "r", stdin);
    /* Init variables */
    int people_num, total, close_time, average_time;        // global control 
    int* eve_time;                  // every person's waiting time
    int people = 0;                 // how many people has in?
    int curr_time = 0;              // the time
    int first_open = 1;             // first window status
    int second_open = 0;            // second window status
    int process_time = 0;           // process time

    /* get variables */
    scanf("%d %d %d %d", &people_num, &total, &close_time, &average_time);

    
    /* Init queues */
    Queue firstQueue = CreateQueue(people_num);         // first queue
    Queue secondQueue = CreateQueue(people_num);        // second queue
    /* TODO: it should be an array */
    Queue allPeople = CreateQueue(people_num);

    /* Init array */
    eve_time = malloc(sizeof(int) * people_num);

    /* Read all people's property into the queue */ 
    for(int i = 0; i < people_num; ++ i) {
        int money;
        int enter_time;

        scanf("%d %d", &money, &enter_time);
        person tmp = malloc(sizeof(struct aPerson));
        tmp->deps_money = money;
        tmp->time = enter_time;
        tmp->num = i + 1;
        tmp->waiting_time = 0;

        Enqueue(tmp, allPeople);
    }

    /* While the bank is not closed -> continue to check people */
    while(curr_time < close_time) {
        // printf("curr_time = %d\n", curr_time);
        if(people < allPeople->size) {
            person tmp = allPeople->arr[people];
            if(tmp->time == curr_time) {
                // printf("En people %d to first queue.\n", people + 1);
                Enqueue(tmp, firstQueue);
                people ++;
            }
        }

        /* Increase the waiting time */


        /* Process the first queue 
         * TODO: make this a function
         */
        if(first_open) {
            person top = Front(firstQueue);
            if(top) {
                if(process_time < average_time) process_time ++;
                /* Check if it is ok */
                int top_money = top->deps_money;
                if(top_money > 0) {
                    /* Let's do it! */
                    if(process_time == average_time) {
                        // printf("people %d in first queue: byebye. ", top->num);
                        total += top_money;
                        // printf("total = %d", total);
                        top->waiting_time -= average_time;
                        Dequeue(firstQueue);
                        process_time = 0;

                        /* Check the second queue 
                        * TODO: make it as a function
                        */
                        int cnt = 0;
                        int found = 0;
                        int sz = secondQueue->size;
                        while(!found) {
                            if(cnt == sz) {
                                break;
                            }
                            person scond_person = Front(secondQueue);
                            if(scond_person->deps_money + total < 0) {
                                /* NO! Go to the REAR! */
                                scond_person = FrontAndDequeue(secondQueue);
                                Enqueue(scond_person, secondQueue);
                                cnt ++;
                            } else {
                                /* OK! Process it first! */
                                // printf("Open second Queue\n");
                                first_open = 0;
                                second_open = 1;
                                found = 1;
                            }
                        }
                    }
                } else {
                    if(top_money + total < 0) {
                        /* No! Go to the second */
                        // printf("Move person %d to second queue.\n", top->num);
                        process_time = 0;          // reset this time
                        FrontAndDequeue(firstQueue);
                        Enqueue(top, secondQueue);
                    } else {
                        /* OK! Byebye! */
                        if(process_time == average_time) {
                            // printf("Goodbye, person %d! ", top->num);
                            top->waiting_time -= average_time;
                            total += top_money;
                            // printf("total = %d", total);
                            Dequeue(firstQueue);
                            process_time = 0;
                        }
                    }
                }
            }
        } else if(second_open) {
            /* The second top is ok */
            person top = Front(secondQueue);
            if(top) {
                if(process_time < average_time) process_time ++;
                if(process_time == average_time) {
                    /* OK! Byebye! */
                    total += top->deps_money;
                    Dequeue(secondQueue);
                    // printf("Byebye, person %d!\n", top->num);
                    top->waiting_time -= average_time;
                    process_time = 0;
                    /* Check again */
                    int found = 0;
                    int cnt = 0;
                    int s = secondQueue->size;
                    while(!found) {
                        if(cnt == s) {
                            break;
                        }
                        person scond_person = Front(secondQueue);
                        if(scond_person->deps_money + total < 0) {
                            /* NO! Go to the REAR! */
                            FrontAndDequeue(secondQueue);
                            Enqueue(scond_person, secondQueue);
                            cnt ++;
                            process_time = 0;
                        } else {
                            /* OK! Process it first! */
                            first_open = 0;
                            second_open = 1;
                            found = 1;
                            process_time = 0;
                        }
                    }

                    if(!found) {
                        /* Go to the first queue */
                        first_open = 1;
                        second_open = 0;
                    }
                }
            }
        }
        // printf("person2, waiting time: %d\n", allPeople->arr[1]->waiting_time);
        /* Update curr_time */
        curr_time ++;
        IncrTime(firstQueue);
        IncrTime(secondQueue);
    }

    /* Print out all */
    int size = allPeople->size;
    for(int i = 0; i < size; ++ i) {
        printf("%d\n", allPeople->arr[i]->waiting_time);
    }
}

void IncrTime(Queue Q) {
    int size = Q->size;
    int fnt = Q->front;
    person* a = Q->arr;

    for(int i = 0, cnt = 0; cnt < size; ++ i, ++ cnt) {
        if(fnt + i == Q->capacity) {
            fnt = 0;
            i = 0;
        }
        a[fnt + i]->waiting_time ++;
    }
}
