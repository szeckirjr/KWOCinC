# Keyword Out Of Context in C

The goal of this project was to code a program that can generate a concordance from a text file, which is an alphabetical list of the principal words used in a text file, listing every instance of each word with its immediate context (line and line number).

# Description of files in this directory.

* ```makefile```: Needed to build the assignment. In order to
construct the ```kwoc3``` executable, enter either ```make``` or
```make kwoc3```.

* ```kwoc3.c```: The C file containing the ```main()``` function.

* ```emalloc.[ch]```: Source code and header file for the
```emalloc``` function. This is kept in its own
source-code file as it can be used independently in both
```kwoc3.c``` and ```listy.c```.

* ```listy.[ch]```: Linked-list routines.

