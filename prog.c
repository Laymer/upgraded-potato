#include <stdio.h>
#include <stdbool.h>

// function declarations
void * how_many_dogs();
void * print_menu();
void * convert_ascii();
void * arithmetic();
bool even(int number);
void * unary_plus_minus();
void * increment_decrement();

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
            printf("Running unary_plus_minus()...\n");
            increment_decrement();
            break;
        default :
            printf("Exiting...\n" );
    }


    return 0;
}

void * how_many_dogs(){
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

void * print_menu(){
    printf("Menu : \n");

    printf("1) how_many_dogs()\n");
    printf("2) convert_ascii()\n");
    printf("3) arithmetic()\n");
    printf("4) unary_plus_minus()\n");
    printf("5) increment_decrement()\n");
}

void * convert_ascii(){
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

void * arithmetic(){
    int x = (2 + ((3 * 4) / 5)) - 2;
    int y = 5 % 2;
    printf("Result of (2 + ((3 * 4) / 5)) - 2 = %d\n", x);
    printf("Result of 5 % 2 = %d\n", y);

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

void * unary_plus_minus(){
    int money = 25;
    int bill = 15;

    int total = money - -bill; // 25 - -15 = 25 + 15 = 40

    printf("Total = %i\n", total);
    printf("Bill = %i\n", bill);
}

void * increment_decrement(){
    int pizzas_to_eat = 100;
    int output = pizzas_to_eat++;
    pizzas_to_eat--;
    printf("Pizzas to eat (output = pizzas_to_eat++): %d\n", output);
    
    output = ++pizzas_to_eat;
    printf("Pizzas to eat (output = ++pizzas_to_eat): %d\n", output);
}