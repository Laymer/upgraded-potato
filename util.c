#include "util.h"    /* Always include the header file that declares something
                     * in the C file that defines it. This makes sure that the
                     * declaration and definition are always in-sync.  Put this
                     * header first in foo.c to ensure the header is self-contained.
                     */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strcpy

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h> // for wait (obviously...)
#include <netdb.h> // for getaddrinfo

#include <netinet/in.h>
#include <arpa/inet.h> // for inet_ntoa
#include <ifaddrs.h> // for getifaddrs 

#include <pthread.h> 

#include <time.h>

#include <signal.h> // SIGKILL

#include <unistd.h>
// #include <conio.h>

void get_interface_addresses(char * ifname, char * address){

    printf("Looking for address of interface %s...\n", ifname);
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char host[NI_MAXHOST];
    char hostaddr[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    getifaddrs(&ifaddr);

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) {
            continue;
        }

        family = ifa->ifa_addr->sa_family;

        /* Display interface name and family (including symbolic
           form of the latter for the common families) */

        printf("%s  address family: %d%s\n",
                ifa->ifa_name, family,
                (family == AF_PACKET) ? " (AF_PACKET)" :
                (family == AF_INET) ?   " (AF_INET)" :
                (family == AF_INET6) ?  " (AF_INET6)" : "");

        if (strcmp(ifname, ifa->ifa_name) == 0 && family == AF_INET) {
            printf("FOUND %s IPv4 !\n", ifname);
            s = getnameinfo(ifa->ifa_addr
                    , sizeof(struct sockaddr_in)
                    , hostaddr
                    , NI_MAXHOST
                    , NULL
                    , 0
                    , NI_NUMERICHOST);
            strncpy(address, hostaddr, NI_MAXHOST);
            printf("IPv4 address of %s : %s\n", ifname, hostaddr);
        }

        /* For an AF_INET* interface address, display the address */

        if (family == AF_INET || family == AF_INET6) {
            s = getnameinfo(ifa->ifa_addr,
                    (family == AF_INET) ? sizeof(struct sockaddr_in) :
                                          sizeof(struct sockaddr_in6),
                    host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }
            printf("\taddress: <%s>\n", host);
        }        
    }
    freeifaddrs(ifaddr);
}

void * routine(){
    int precision = 10;
    int loop=100000; // increase this value to get more digits of PI number
    srand(10102020); // more secure rand...
    printf("PI is %.*lf\n", precision, pi(loop));
}

void thread_the_needle(){
    printf("we got some nice threads here hehe :)\n");
    
    // Just to get the room nice and warm :)
    int numofcpus = sysconf(_SC_NPROCESSORS_ONLN); // Get the number of logical CPUs.
    
    pthread_t workers[32];

    for (int i = 0; i < 32; ++i)
    {
        pthread_create(&workers[i]
            , NULL
            , &routine // pass reference to function
            , NULL);        
    }

    for (int i = 0; i < 32; ++i)
    {
        pthread_join(workers[i]
            , NULL);        
    }
}

int power(int x, unsigned int y){
    if( y == 0)
        return 1;

    int t = power(x, y/2);  // power is called only once instead of twice.

    return y%2 ? x*t*t : t*t;
}

// Max Base
// Monte-Carlo Calculation of Pi
// GitHub.com/BaseMax/pi
// A better and alternative way to create random number: https://github.com/BaseMax/SecureRandStringC
double pi(int loop) {
    int count=0;
    for(int i=0;i<loop;i++) {
        double a=(double)rand()/RAND_MAX;
        double b=(double)rand()/RAND_MAX;
        if(1>=a*a+b*b)
            count++;
    }
    return (double)count/loop*4;
}

void * we_are_not_procs(){
    printf("we are threads !\n");
}

void threads_vs_procs(){
    printf("threads are cool but what about procs? :o\n");

    // procs
    int pid = fork();
    if (pid == -1)
    {
        perror("OH NO ! :(");
    }

    if (pid == 0)
    {
        printf("Child : Hi I am the kid\n"); // pid = 0 is returned to child proc
    } else {
        printf("Parent : Hi I am the papa\n"); // pid > 0 is returned to parent proc
        // kill(pid,SIGKILL); --> uncomment this line for bad parenting (kid = dead)
        wait(NULL); // to wait until child has finished
        printf("Parent : I think something happened to my kid :/\n");
    }
    if (pid > 0)
    {
        // parent
        // pthreads
        pthread_t threadz[2];
        int array_len = sizeof(threadz) / sizeof(pthread_t);
        printf("number of elements : %d\n", array_len);

        for (int i = 0; i < array_len; ++i)
        {
            pthread_create(&threadz[i]
                , NULL
                , &we_are_not_procs
                , NULL);
        }

        for (int i = 0; i < array_len; ++i)
        {
            pthread_join(threadz[i]
                , NULL);
        }
    }

    if (pid == 0)
    {
        printf("Child : still alive ahah !\n"); // if SIGKILL is sent before wait(NULL) this line is not printed
    }
}

void remember_to_free(){

    // function signature :
    // 
    // void *malloc(size_t size) // size is the size of the memory block in bytes
    // 
    // returns a pointer to the first byte of allocated block or NULL if it fails 

    // void * calloc(size_t num, size_t size) // allocates a block of (num * size)
    // ----> calloc also initializes the block by zeroing everything :) 

    // void * realloc(void * ptr, size_t size) // reallocates data at ptr to a new block
    // of size "size", either by allocating a whole new block or by extending the one at ptr

    char * str;
    char * p;
    /* Initial memory allocation */
    // str = (char *) malloc(16);
    str = (char *) calloc(16, sizeof(char));
    strcpy(str, "tutorialspoint");

    for (p = str; *p; p++) // at the end of a string, *p evaluates to zero ('\0') thus false and loop terminates
    {
        printf("Character = %c,  Address = %u\n", *p, p);
    }

    // strcpy(str, "tutorialspoint-tutorialspoint"); // produces a warning :
    // warning: ‘__builtin_memcpy’ writing 30 bytes into a region of size 16 overflows the destination
    printf("----------------------------------------------------\n");
    str = (char *) realloc(str, 32 * sizeof(char));
    
    strcpy(str, "tutorialspoint-tutorialspoint"); // cool :)

    for (p = str; *p; p++) // at the end of a string, *p evaluates to zero ('\0') thus false and loop terminates
    {
        printf("Character = %c,  Address = %u\n", *p, p);
    }

    free(str); // I ACTUALLY FORGOT TO DO IT OMG !!!
}