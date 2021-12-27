# The upgraded-potato
Learning C programming again for fun :)

## Random notes I found interesting

*   [Character Conversion](#character-conversion)
    *   [Leading blank for `scanf()`](#leading-blank-for-scanf)
*   [Operators](#operators)
    *   [Ternary operators](#ternary-operators)
    *   [Unary operators](#unary-operators)
*   [Pointers](#pointers)
    *   [Pointers to struct fields](#pointers-to-struct-fields)
*   [Miscellaneous](#miscellaneous)
    *   [I C what you did there](#i-c-what-you-did-there)

* * *

### Character Conversion

#### Leading blank for `scanf()`

From [this post](https://stackoverflow.com/questions/5240789/scanf-leaves-the-newline-character-in-the-buffer) on StackOverflow :

*Use `" %c"` with a leading blank to skip optional white space. Do not use a trailing blank in a `scanf()` format string.*

Without doing this, `scanf()` was not actually waiting for user input
but taking the **LF** as input (Printing out the variable showed ASCII char '10', Line Feed).

```
    char ascii_char;
    printf("Please enter a char: ");
    scanf(" %c", &ascii_char); --> HERE
    printf("%i\n", ascii_char);
```

### Operators

#### Ternary operators

It's always nice to use ternary operators. They look like this :

```
bool isEven = ((number % 2) == 0) ? true : false;
```

#### Unary operators

In the example below :

```
    int pizzas_to_eat = 100;
    int output = pizzas_to_eat++;
```

The value of `output` is set to **100** :pushpin: :heavy_exclamation_mark: :100: :warning:

The unary operator `++` increases the value of `pizzas_to_eat` only after it's value
was assigned to `output`.

To increment the value of `pizzas_to_eat` **BEFORE** assigning it's value to `output`,
the operator needs to be placed before the variable :

```
    int pizzas_to_eat = 100;
    int output = ++pizzas_to_eat;
```

Here the value of `output` will be **101** :heavy_exclamation_mark:

### Pointers

#### Pointers to struct fields

From [OverIQ](https://overiq.com/c-programming-101/pointer-to-a-structure-in-c/) :

* * *
There are two ways of accessing members of structure using pointer:

    - Using indirection (*) operator and dot (.) operator.
    - Using arrow (->) operator or membership operator.
* * *

This means :

`(*person).age` (here `person` holds the struct itself)

is equivalent to :

`person->age` (here `person` holds the address of the struct)


### Miscellaneous

#### I C what you did there
![Alt Text](https://media.giphy.com/media/vFKqnCdLPNOKc/giphy.gif)