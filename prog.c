#include "util.h"
#include "workout.h"
#include "gui.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // for strcpy

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h> // for getaddrinfo

#include <netinet/in.h>
#include <arpa/inet.h> // for inet_ntoa
#include <ifaddrs.h> // for getifaddrs

// Function declarations

// Practice
void how_many_dogs();
void print_menu();
void convert_ascii();
void arithmetic();
bool even(int number);
void unary_plus_minus();
void increment_decrement();

// Socket functions
void server();

// Utility functions
void print_address(struct sockaddr_in * address, int server_or_client);

// Threading
void fun_with_threads();

int main(int argc, char const *argv[])
{

    print_menu();
    
    /* local variable definition */
    int menu_option;
    scanf("%i", &menu_option);
    switch(menu_option) {
        case 1 :
            printf("Running how_many_dogs()...\n" );
            how_many_dogs();
            break;
        case 2 :
            printf("Running convert_ascii()...\n");
            convert_ascii();
            break;
        case 3 :
            printf("Running arithmetic()...\n");
            arithmetic();
            break;
        case 4 :
            printf("Running unary_plus_minus()...\n");
            unary_plus_minus();
            break;
        case 5 :
            printf("Running increment_decrement()...\n");
            increment_decrement();
            break;
        case 6 :
            printf("Running server()...\n");
            server();
            break;
        case 7 :
            printf("Running get_interface_addresses(\"eth0\", args)...\n");
            char ifaddr[NI_MAXHOST];
            get_interface_addresses("eth0", ifaddr);
            printf("RESULT = %s\n", ifaddr);
            break;
        case 8 :
            printf("Running fun_with_threads()...\n");
            fun_with_threads();
            break;
        case 9 :
            printf("Running threads_vs_procs()...\n");
            threads_vs_procs();
            break;
        case 10 :
            printf("Running remember_to_free()...\n");
            remember_to_free();
            break;
        case 11 :
            printf("Running training_database()...\n");
            training_database();
            break;
        default :
            printf("Exiting...\n" );
    }

    exit(0);
    // return 0;
}

void how_many_dogs(){
    double dogs;

    printf("How many dogs do you have? ");
    scanf("%lf", &dogs);

    // printf("%i\n", dogs);
    printf("%f\n", dogs);
    printf("%e\n", dogs);
    printf("%g\n", dogs);

    /* Conversion characters
    ------------------------
    %f - Decimal
    %e - Scientific
    %g - Auto ( scientific if more than 5 digits )
    */
}

void print_menu(){
    printf("Menu : \n");

    printf("1) how_many_dogs()\n");
    printf("2) convert_ascii()\n");
    printf("3) arithmetic()\n");
    printf("4) unary_plus_minus()\n");
    printf("5) increment_decrement()\n");
    printf("6) server()\n");
    printf("7) get_interface_addresses()\n");
    printf("8) fun_with_threads()\n");
    printf("9) threads_vs_procs()\n");
    printf("10) remember_to_free()\n");
    printf("11) training_database()\n");
}

void convert_ascii(){
    char ascii_char;
    printf("Please enter a char: ");
    // LEADING BLANK IN FRONT OF CONVERSION CHARACTER FOR SCANF !
    // -> https://stackoverflow.com/questions/5240789/scanf-leaves-the-newline-character-in-the-buffer
    scanf(" %c", &ascii_char);
    printf("%i\n", ascii_char);

    int integer;
    printf("Please enter an integer (0 - 127): ");
    scanf("%d", &integer);
    printf("%c\n", integer);

    printf("Here's some bonus math with chars (: :\n");
    char mathz = 'A' + '\t';
    printf("A(65) + \\t(11) = %c(%d)\n", mathz, mathz);
}

void arithmetic(){
    int x = (2 + ((3 * 4) / 5)) - 2;
    int y = 5 % 2;
    printf("Result of (2 + ((3 * 4) / 5)) - 2 = %d\n", x);
    printf("Result of 5 mod 2 = %d\n", y);

    // Sharing pizza with your pet rat, Pepper.
    // There are 6 pieces of pizza, that can not be split in half

    int pieces_of_pizza = 6;
    int number_of_eaters = 2;
    int leftover = pieces_of_pizza % number_of_eaters;

    printf("Leftover pieces of pizza = %d\n", leftover);
    printf("Is the leftover even or odd?\n");
    if (even(leftover))
    {
        printf("the leftover is an even number !\n");
    } else {
        printf("the leftover is an odd number !\n");
    }        
}

bool even(int number){
    return ((number % 2) == 0) ? true : false;
}

void unary_plus_minus(){
    int money = 25;
    int bill = 15;

    int total = money - -bill; // 25 - -15 = 25 + 15 = 40

    printf("Total = %i\n", total);
    printf("Bill = %i\n", bill);
}

void increment_decrement(){
    int pizzas_to_eat = 100;
    int output = pizzas_to_eat++;
    pizzas_to_eat--;
    printf("Pizzas to eat (output = pizzas_to_eat++): %d\n", output);
    
    output = ++pizzas_to_eat;
    printf("Pizzas to eat (output = ++pizzas_to_eat): %d\n", output);
}

void server(){
    printf("Hi ! I'm a server ! :)\n");

    char server_msg[256] = "Hi, I am happy server :)";

    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0); // same parameters as for client socket

    // define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9999);

    char ifaddr[NI_MAXHOST];
    get_interface_addresses("eth0", ifaddr);
    printf("HOST ADDR : %s\n", ifaddr);

    inet_aton(ifaddr, &server_address.sin_addr);
    print_address(&server_address, SERVER);


    // bind the socket to specified IP address and port
    bind(sock, (struct sockaddr *) &server_address, sizeof(server_address));
    printf("Socket is bound\n");

    // start listening
    listen(sock         // socket
            , 5);       // backlog
    /*
        The backlog, defines the maximum length to which 
        the queue of pending connections for sockfd may grow. 
        If a connection request arrives when the queue is full, 
        the client may receive an error with an indication of ECONNREFUSED.
    */

    printf("Socket is listening...\n");

    // client socket
    int client_sock;
    struct sockaddr_in client_address;
    int addrlen = sizeof(client_address);

    // accept -> puts socket into ESTABLISHED state
    client_sock = accept(sock                   // server socket
        , (struct sockaddr *) &client_address   // client address
        , (socklen_t *) &addrlen);              // size of client address
    
    print_address(&client_address, CLIENT);

    send(client_sock            // client socket to send to
        , server_msg            // message
        , sizeof(server_msg)    // size of the message
        , 0);                   // optional flag

    printf("Done sending :) bye...\n");
}

/*
    server : 1
    client : 0
*/
void print_address(struct sockaddr_in * address, int server_or_client){
    char endpoint[7]; // 6 characters + string termination char '\0'
    memset(endpoint, '\0', sizeof(endpoint));


    switch(server_or_client) {
        case SERVER :
            strcpy(endpoint, "Server");
            break;
        case CLIENT :
            strcpy(endpoint, "Client");
            break;
        default :
            printf("[ERROR] Unknown endpoint type given to print_address() : %d\n"
                , server_or_client);
    }
    printf("%s address family : %d\n", endpoint, address->sin_family);
    printf("%s address port : %d\n", endpoint, ntohs(address->sin_port));
    printf("%s address IP : %s\n", endpoint, inet_ntoa(address->sin_addr));
}


void fun_with_threads(){
    thread_the_needle();
}
