# Miscellaneous

This git repository is a collection of random scripts that
were written by me.

## textwrap
*textwrap* is a Python 3 script, that wraps long lines in files or
standard output with proper line breaks so they fit on the screen.
This is basically a stripped down version of “fmt,” but it is
Unicode-aware.

**license**: GPLv2

## fprm
*fprm* is a C90 program that prints file permissions of the form
as “ls” does (e.g. “-rwxr-xr-x”).

**license**: GPLv2

### Build Instructions
I tested fprm on Linux 3.2 with GCC 4.6 and GNU make 3.81, but it
should be compatible with any POSIX-compliant system and
C90-compliant C compiler.

        cc -ansi -O3 -o fprm fprm.c
