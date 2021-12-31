#ifndef WORKOUT_DOT_H    /* This is an "include guard" */
#define WORKOUT_DOT_H    /* prevents the file from being included twice. */
                     /* Including a header file twice causes all kinds */
                     /* of interesting problems.*/

/**
 *
 * Nice structs bro
 *
 */

typedef struct exercise {
    char                 name[255];
    int                  reps;
    int                  sets;
    float                weight;
    struct exercise *    next;
} exercise;

/**
 * This is a function declaration.
 * It tells the compiler that the function exists somewhere.
 */
void training_database();
void print_exercise(exercise ex);
exercise create_exercise(const char name[255], int reps, int sets, float weight, exercise * next);

#endif /* WORKOUT_DOT_H */