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
    exercise ex1 = create_exercise("Squat", 8, 4, 95.0, NULL);
    exercise ex2 = create_exercise("Deadlift", 6, 4, 120.0, NULL);

    ex1.next = &ex2;

    // print_exercise(ex1);
    // print_exercise(ex2);

    workout wk;
    strcpy(wk.name, "Hypertrophy training");

    enqueue_exercise(&wk, &ex1);
    // enqueue_exercise(wk, ex2);
    print_workout(&wk);
}

void print_exercise(exercise * ex){
    printf("Exercise name : %s\n", ex->name);
    printf("Number of repetitions per set : %d\n", ex->reps);
    printf("Number of sets : %d\n", ex->sets);
    printf("Exercise weight : %.2f Kg\n", ex->weight);

    if (ex->next != NULL)
    {
        printf("Next exercise name : %s\n", ex->next->name);
    }
}

exercise create_exercise(const char name[255]
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
        strcpy(new->name, name);
        new->reps = reps;
        new->sets = sets;
        new->weight = weight;
        new->next = next;

        return *new;
    }
}

void print_workout(workout * wk){
    printf("Workout name : %s\n", wk->name);

    if (wk->exercises == NULL)
    {
        printf("Workout %s exercises is NULL\n", wk->name);
    } else {
        exercise * current = (struct exercise *) malloc(sizeof(struct exercise));
        current = wk->exercises;
        while(current != NULL) {

            printf("Printing exercise from %s\n", wk->name);
            print_exercise(current);
            current = current->next;
        }
        free(current);
        printf("exercise name : %s\n", wk->exercises->name);
    }
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

