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

    exercise * head = NULL;
    exercise * current = NULL;

    exercise ex2 = create_exercise("Deadlift", 6, 4, 120.0, NULL);

    ex1.next = &ex2;

    print_exercise(ex1);
    print_exercise(ex2);

}

void print_exercise(exercise ex){
    printf("Exercise name : %s\n", ex.name);
    printf("Number of repetitions per set : %d\n", ex.reps);
    printf("Number of sets : %d\n", ex.sets);
    printf("Exercise weight : %.2f Kg\n", ex.weight);

    if (ex.next != NULL)
    {
        printf("Next exercise name : %s\n", ex.next->name);
    }
}

exercise create_exercise(const char name[255]
                            , int reps
                            , int sets
                            , float weight
                            , exercise * next){

    exercise new;
    strcpy(new.name, name);
    new.reps = reps;
    new.sets = sets;
    new.weight = weight;
    new.next = next;

    return new;
}