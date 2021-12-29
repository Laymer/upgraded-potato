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
*   [Threads and Procs](#threads-and-procs)
    *   [Why does a printf after `fork()` display twice?](#why-does-a-printf-after-fork-display-twice)
*   [Miscellaneous](#miscellaneous)
    *   [Math `pow()` function](#math-pow-function)
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

### Threads and Procs

#### Why does a printf after `fork()` display twice?

So here you are, just chilling, and occasionally doing a call to `fork()`,
and of course being careful you want to make sure it worked, BUT THEN ...

```
    int pid = fork();
    if (pid == -1)
    {
        perror("OH NO ! :(");
    } else {
        printf("OH YEAH ! :)\n");
    }
```

Outputs :

```
OH YEAH ! :)
OH YEAH ! :)
```

So at first, my face was like : " :thinking: :thinking: :thinking: " ...

But then I read [this](https://www.geeksforgeeks.org/fork-system-call/) ! Duh !
Had I read some docs earlier or remembered my C course from uni
this would have been obvious ! 

**AFTER THE LINE WHERE `fork()` IS CALLED, THE SAME CODE IS EXECUTED BY BOTH CHILD AND PARENT PROC !**

Instead of printing as described above, the alternative below is preferred :

```
    if (pid == 0)
    {
        printf("Hi I am the kid\n"); // pid = 0 is returned to child proc
    } else {
        printf("Hi I am the papa\n"); // pid > 0 is returned to parent proc
    }
```

What it looks like with 3 consecutive calls to `fork()` (8 procs in total since 2³ = ) :

Source : [`fork()` in C](https://www.geeksforgeeks.org/fork-system-call/) from GeeksforGeeks.

```
fork ();   // Line 1
fork ();   // Line 2
fork ();   // Line 3

       L1       // There will be 1 child process 
    /     \     // created by line 1.
  L2      L2    // There will be 2 child processes
 /  \    /  \   //  created by line 2
L3  L3  L3  L3  // There will be 4 child processes 
                // created by line 3

```

So there are total eight processes (new child processes and one original process).

If we want to represent the relationship between the processes as a tree hierarchy it would be the following:

The main process: P0
Processes created by the 1st fork: P1
Processes created by the 2nd fork: P2, P3
Processes created by the 3rd fork: P4, P5, P6, P7

```
            P0        
         /  |   \     
       P1   P4   P2   
      /  \         \  
    P3    P6        P5
   /                  
 P7
```
    
### Miscellaneous

#### Math `pow()` function

Trying to use the `math.h` function `pow()`, 
I ran into the error described [in this post](https://stackoverflow.com/questions/12824134/undefined-reference-to-pow-in-c-despite-including-math-h).

For some reason even with the linker flag, I kept getting the same error
so I just wrote a power function :smile:

#### I C what you did there
![Alt Text](https://media.giphy.com/media/vFKqnCdLPNOKc/giphy.gif)