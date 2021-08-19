# Keyword Out Of Context in C

The goal of this project was to code a program that can generate a concordance from a text file, which is an alphabetical list of the principal words used in a text file, listing every instance of each word with its immediate context (line and line number).

OBS: A version of this program also exists in Python, located in [this repo](https://github.com/szeckirjr/KWOCinPython).

# Description of files in this directory

* ```makefile```: Needed to build the assignment. In order to
construct the ```kwoc3``` executable, enter either ```make``` or
```make kwoc3```.

* ```kwoc3.c```: The C file containing the ```main()``` function.

* ```emalloc.[ch]```: Source code and header file for the
```emalloc``` function. This is kept in its own
source-code file as it can be used independently in both
```kwoc3.c``` and ```listy.c```.

* ```listy.[ch]```: Linked-list routines.

# How to run the program

After using ```make``` to generate the file, use the following:
```./kwoc3 [INPUT-FILE] (-e) [EXCEPTION-FILE]```
