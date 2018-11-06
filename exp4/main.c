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
    while(curr_time <= close_time) {
        if(people > allPeople->size) {
            person tmp = allPeople->arr[people];
            if(tmp->time == curr_time) {
                Enqueue(tmp, firstQueue);
                people ++;
            }
        }

        /* Increase the waiting time */
        IncrTime(firstQueue);
        IncrTime(secondQueue);

        /* Process the first queue 
         * TODO: make this a function
         */
        if(first_open) {
            person top = Front(firstQueue);
            process_time ++;
            if(process_time == average_time) {
                /* Check if it is ok */
                int top_money = top->deps_money;
                if(top_money > 0) {
                    /* OK! finished! Byebye! */
                    total += top_money;
                    Dequeue(firstQueue);
                    process_time = 0;
                    /* Check the second queue */
                    int job_done = 0;
                    while(!job_done) {
                        person scond_person = Front(secondQueue);
                        if(scond_person->deps_money + total < 0) {
                            /* NO! Go to the REAR! */
                            scond_person = FrontAndDequeue(secondQueue);
                            Enqueue(scond_person, secondQueue);
                        } else {
                            /* OK! Process it first! */
                            first_open = 0;
                            second_open = 1;
                            job_done = 1;
                        }
                    }
                } else {
                    if(top_money + total < 0) {
                        /* No! Go to the second */
                        process_time = 0;          // reset this time
                        FrontAndDequeue(firstQueue);
                        Enqueue(top, secondQueue);
                    } else {
                        /* OK! Byebye! */
                        total += top_money;
                        Dequeue(secondQueue);
                    }
                }
            }
        } else if(second_open) {
            /* The second top is ok */
            person top = FrontAndDequeue(secondQueue);
            process_time;
            if(process_time == average_time) {
                /* OK! Byebye! */
                total += top->deps_money;
                Dequeue(secondQueue);
            }
        }
    }
}
