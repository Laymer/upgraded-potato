#include <stdio.h>

// function declarations
void * how_many_dogs();
void * print_menu();
void * convert_ascii();
void * arithmetic();

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
    int x = 2 + 3 * 4 / 5 - 6
}
