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

	$ cc -Os -o fprm fprm.c -ansi
