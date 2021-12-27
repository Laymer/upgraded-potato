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
#include <netdb.h> // for getaddrinfo

#include <netinet/in.h>
#include <arpa/inet.h> // for inet_ntoa
#include <ifaddrs.h> // for getifaddrs

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
    return;
}