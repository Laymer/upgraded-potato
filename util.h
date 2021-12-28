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

/**
 * This is a function declaration.
 * It tells the compiler that the function exists somewhere.
 */
void get_interface_addresses(char * ifname, char * address);
void thread_the_needle();
void * routine();
int power(int x, unsigned int y);
double pi(int loop);

#endif /* UTIL_DOT_H */