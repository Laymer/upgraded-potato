#include "util.h"    /* Always include the header file that declares something
                     * in the C file that defines it. This makes sure that the
                     * declaration and definition are always in-sync.  Put this
                     * header first in foo.c to ensure the header is self-contained.
                     */
#include "workout.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strcpy

void training_database(){
    read_csv_file();
//    char name1[255], name2[255];
//    strcpy(name1, "Squat");
//    strcpy(name2, "Deadlift");
//    exercise * ex1 = create_exercise(name1, 8, 4, 95.0, NULL);
//    exercise * ex2 = create_exercise(name2, 6, 4, 120.0, NULL);
//
//    ex1->next = ex2;
//
//    // print_exercise(ex1);
//    // print_exercise(ex2);
//
//    workout * wk = (struct workout *) malloc(sizeof(struct workout));
//    strcpy(wk->name, "Hypertrophy training");
//    wk->exercises = ex1;
//    ex1->next = ex2;
////    enqueue_exercise(wk, ex1);
//    // enqueue_exercise(wk, ex2);
//    print_workout(wk);
//    free(wk);
//    free(ex1);
//    free(ex2);
}

void print_exercise(exercise * ex){
    if (ex != NULL)
    {
        printf("Exercise name : %s\n", ex->name);
        printf("Number of repetitions per set : %d\n", ex->reps);
        printf("Number of sets : %d\n", ex->sets);
        printf("Exercise weight : %.2f Kg\n", ex->weight);
    }
}

exercise * create_exercise(const char name[255]
                            , int reps
                            , int sets
                            , float weight
                            , exercise * next){

    exercise * new = (struct exercise *) malloc(sizeof(struct exercise));

    if (new == NULL)
    {
        printf("[ERROR] could not allocate memory for exercise\n");
        exit(1);
    } else {
        memset(new->name, '\0', sizeof(new->name));
        strcpy(new->name, name);
        new->reps = reps;
        new->sets = sets;
        new->weight = weight;
        new->next = next;

        return new;
    }
}

void print_workout(workout * wk){

     if (wk != NULL)
     {
         exercise * current = wk->exercises;
         while (current != NULL){
             print_exercise(current);
             current = current->next;
         }
     }
    //     printf("Workout name : %s\n", wk->name);

    //     if (wk->exercises == NULL)
    //     {
    //         printf("Workout %s exercises is NULL\n", wk->name);
    //     } else {
    //     }
    // if (wk.exercises != NULL)
    // {
    //     for (ptr = wk.exercises; ptr; ++ptr)
    //     {
    //         print_exercise(*ptr);
    //     }
    // } else {
    //     printf("Workout is empty\n");
    // }
}

void enqueue_exercise(workout * wk, exercise * ex){
    // print_exercise(ex);

    if (wk->exercises == NULL)
    {
        printf("Workout has no exercises, enqueuing at head...\n");
        wk->exercises = (struct exercise *) malloc(sizeof(struct exercise));

        if (wk->exercises == NULL)
        {
            printf("[ERROR] could not allocate memory for exercise while enqueuing\n");
            exit(1);
        }

        // memcpy(wk->exercises, ex, sizeof(struct exercise));
        wk->exercises = ex;

    } else {
        printf("iterating to end of linked list\n");
    }
}

void read_csv_file(){
    FILE* stream = fopen("exercises.csv", "r");
    char line[1024];
    int header_flag = 1;

    while (fgets(line, 1024, stream)){

        if (header_flag){
            header_flag = 0;
            continue;
        }

        if (strcmp(line, "\n") == 0){
            continue;
        }
        char * buffer = strdup(line);
        const char * token;
        int index = 0;

        char name[255];
        int reps, sets;
        float weight;


        for (token = strtok(line, ",");
            token && *token;
            token = strtok(NULL, ",\n")) {

            switch (index) {
                case 1:
                    strcpy(name, token);
                    break;
                case 2:
                    reps = strtol(token, NULL, 10);
                    break;
                case 3:
                    sets = strtol(token, NULL, 10);
                    break;
                case 4:
                    weight = strtof(token, NULL);
                    break;
                default:
                    printf("Tokens[%d] : %s\n", index, token);
            }
            ++index;
        }
        exercise * ex = create_exercise(name, reps, sets, weight, NULL);
        print_exercise(ex);
        free(buffer);
    }
}