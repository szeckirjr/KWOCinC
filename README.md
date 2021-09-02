# Keyword Out Of Context in C

The goal of this project was to code a program that can generate a concordance from a text file, which is an alphabetical list of the principal words used in a text file, listing every instance of each word with its immediate context (line and line number).

OBS: A version of this program also exists in Python, located in [this repo](https://github.com/szeckirjr/KWOCinPython).

# Description of files in this directory

- `makefile`: Needed to build the assignment. In order to
  construct the `kwoc3` executable, enter either `make` or
  `make kwoc3`.

- `kwoc3.c`: The C file containing the `main()` function.

- `emalloc.[ch]`: Source code and header file for the
  `emalloc` function. This is kept in its own
  source-code file as it can be used independently in both
  `kwoc3.c` and `listy.c`.

- `listy.[ch]`: Linked-list routines.

# How to run the program

Use `make` to generate the executable file

Then, use the following to run the program: `./kwoc3 [INPUT-FILE] (-e) [EXCEPTION-FILE]`

The tests are described under the [`TESTS.md`](https://github.com/szeckirjr/KWOCinC/blob/master/TESTS.md) file.

If you want to validate the output is correct, you can compare the input file `inXX.txt` with the expected output file `outXX.txt` using `diff` as follows:
`./kwoc3 [INPUT-FILE] (-e) [EXCEPTION-FILE] | diff - [OUTPUT-FILE]`

If you get no output, that means the output from the program is the same as the expected output.

Example test command:
`./kwoc3 Test_Files/in04.txt -e Test_Files/english.txt | diff - Test_Files/out04.txt`
