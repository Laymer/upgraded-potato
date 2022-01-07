# The upgraded-potato
Learning C programming again for fun :)

<img src="https://yt3.ggpht.com/a/AGF-l79REyhoc8SBId2NuI6fb7bUpodJz4tGKjYgNQ=s900-c-k-c0xffffffff-no-rj-mo" data-canonical-src="https://yt3.ggpht.com/a/AGF-l79REyhoc8SBId2NuI6fb7bUpodJz4tGKjYgNQ=s900-c-k-c0xffffffff-no-rj-mo" width="400" height="400" />

## Random notes I found interesting

* [Character Conversion](#character-conversion)
    *   [Leading blank for `scanf()`](#leading-blank-for-scanf)
* [Operators](#operators)
    *   [Ternary operators](#ternary-operators)
    *   [Unary operators](#unary-operators)
* [Pointers](#pointers)
    *   [Pointers to struct fields](#pointers-to-struct-fields)
* [Threads and Procs](#threads-and-procs)
    *   [Why does a printf after `fork()` display twice?](#why-does-a-printf-after-fork-display-twice)
* [Debugging](#debugging)
*   *   [Valgrind](#valgrind)
* [GTK](#gtk)
    *   [Installing GTK](#installing-gtk)
    *   [Compiling GTK](#compiling-gtk)
    *   [Learning GTK](#learning-gtk)
* [Miscellaneous](#miscellaneous)
    *   [Math `pow()` function](#math-pow-function)
    *   [`printf` function outputs unwanted characters](#printf-function-outputs-unwanted-characters)
    *   [Interesting stuff to do](#interesting-stuff-to-do)
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

#### "Address of" and "value of" operators

Always good to have a reminder of this : 

```
int a = 100;

*ptr = &a;

```

Second line : **declaring a pointer to an integer and initializing it with address of a.**

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

- The main process: P0
- Processes created by the 1st fork: P1
- Processes created by the 2nd fork: P2, P3
- Processes created by the 3rd fork: P4, P5, P6, P7

```
            P0        
         /  |   \     
       P1   P4   P2   
      /  \         \  
    P3    P6        P5
   /                  
 P7
```
### Debugging

#### Valgrind
How to track memory leaks using Valgrind :

```
valgrind --leak-check=yes --track-origins=yes -s ./program
```

And the most satisfying output you can possibly imagine having from that is
something that looks like :

```
==41563== HEAP SUMMARY:
==41563==     in use at exit: 0 bytes in 0 blocks
==41563==   total heap usage: 5 allocs, 5 frees, 2,880 bytes allocated
==41563== 
==41563== All heap blocks were freed -- no leaks are possible
==41563== 
==41563== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

**Never forget to free !**

### GTK

#### Installing GTK

To install GTK version 4 (latest at time of writing) :

```
sudo apt install libgtk-4-dev
```

to install version 3 (more stable ?) :

```
sudo apt install libgtk-3-dev
```

#### Compiling GTK

For some reason the exact same command works in terminal but produces an
error using make.

Compiling with output :

```
gcc $( pkg-config --cflags gtk4 ) -o gui gui.c $( pkg-config --libs gtk4 )
```

**NOTE** : having a `main` function is mandatory, otherwise the linker will fail.  

#### Learning GTK

Some pretty cool references I found :

* [GTK Tutorial](https://github.com/ToshioCP/Gtk4-tutorial)
* [GTK Drag n Drop](https://github.com/aeldemery/gtk4_dnd)

### Miscellaneous

#### Math `pow()` function

Trying to use the `math.h` function `pow()`, 
I ran into the error described [in this post](https://stackoverflow.com/questions/12824134/undefined-reference-to-pow-in-c-despite-including-math-h).

For some reason even with the linker flag, I kept getting the same error
so I just wrote a power function :smile:

#### `printf` function outputs unwanted characters

Sometimes you just need to print out things to console to see what you're doing.
But sometimes you also end up with random gibberish characters on top of your output.

For example :

![What the heck is this?](https://imgur.com/522jQC6.png)

Fortunately, some smart people helped me figure out why such event may come to occur.
Quoting a reply on [this post](https://stackoverflow.com/a/49693582) : 

*Therefore, if the last character in your array isn't 0, the above loop will continue until there happens to be a 0 somewhere in the memory that follows.*

Since the `bit_wisdom` function was returning an array of characters without a terminating zero,
calling `printf` on the result with a string conversion character (`%s`) would loop through the array,
print the whole thing and then keep printing characters because `'\0'` was never used.

So instead of returning an array of 32 characters, I changed `bit_wisdom` to return
an array of 33 characters, all set to `'\0'` using `memset` at the beginning and of which
the first 32 would be filled with the binary representation of the number.

The result is a clean print : :smile: 

![What the heck is this?](https://imgur.com/MhR9J2F.png)

#### Interesting stuff to do

* Bitwise calculus
* Protocols (HTTP, FTP, etc.)
* Vector/Matrix calculus
* Kernel modules

#### I C what you did there
![Smol kotik](https://media.giphy.com/media/vFKqnCdLPNOKc/giphy.gif)
