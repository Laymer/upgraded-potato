# The upgraded-potato
Learning C programming again for fun :)

## Random notes I found interesting

*   [Character Conversion](#character-conversion)
    *   [Leading blank for `scanf()`](#leading-blank-for-scanf)
*   [Miscellaneous](#miscellaneous)
    *   [I C what you did there](#i-c-what-you-did-there)

* * *

### Character Conversion

#### Leading blank for `scanf()`

From [this post](https://stackoverflow.com/questions/5240789/scanf-leaves-the-newline-character-in-the-buffer) on StackOverflow :

*Use `" %c"` with a leading blank to skip optional white space. Do not use a trailing blank in a `scanf()` format string.*

Without doing this, `scanf()` was not actually waiting for user input
but taking the **LF** as input (Printing out the variable showed ASCII char '10', Line Feed).

### Miscellaneous

#### I C what you did there
![Alt Text](https://media.giphy.com/media/vFKqnCdLPNOKc/giphy.gif)