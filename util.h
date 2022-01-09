#ifndef UTIL_DOT_H    /* This is an "include guard" */
#define UTIL_DOT_H    /* prevents the file from being included twice. */
                     /* Including a header file twice causes all kinds */
                     /* of interesting problems.*/
#ifndef SERVER
#define SERVER 1
#endif

#ifndef CLIENT
#define CLIENT 0
#endif

#ifndef ARRAY_LEN
#define ARRAY_LEN 3
#endif

/**
 * This is a function declaration.
 * It tells the compiler that the function exists somewhere.
 */
void get_interface_addresses(char * ifname, char * address);
void thread_the_needle();
void * routine();
int power(int x, unsigned int y);
double pi(int loop);
void threads_vs_procs();
void remember_to_free();
void bit_wisdom();
char * showbits(unsigned int x);
int * v_multiply(int v1[], int v2[], int length);
int * v_addition(int v1[], int v2[], int length);
#endif /* UTIL_DOT_H */