# Useful Programs
This git repository is a collection of — in my opinion — useful scripts that
were written by me (Jakob Kramer).

## textwrap
*textwrap* is a Python 3 script that wraps long lines in files and program
output with proper line breaks, so they fit on the screen.

**license**: GPLv2

## fprm
*fprm* is a C90 program that prints file permissions as “ls” does.

**license**: GPLv2

### Build Instructions
I tested fprm on Linux 3.2 with GCC 4.6 and GNU make 3.81, but it should be
compatible with any POSIX-compliant system and C90-compliant C compiler.

	cc -ansi -O3 -o fprm fprm.c
