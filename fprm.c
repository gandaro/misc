/*
 *  fprm - print file permissions similar to `ls'
 *  Copyright (C) 2012  Jakob Kramer <jakob.kramer@gmx.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

void errexit(const char *str) {
    if (errno)
        fprintf(stderr, "%s: %s\n", str, strerror(errno));
    else
        fprintf(stderr, "%s\n", str);

    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    int i, j;
    struct stat s;
    char output[] = "----------";

    if (argc != 2)
        errexit("usage: fprm FILE");

    if (stat(argv[1], &s) == -1)
        errexit("fprm: stat() failed");

    if (S_ISDIR(s.st_mode))
        output[0] = 'd';

    for (i = 0100, j = 0; i >= 1 && j <= 9; i /= 010, j += 3) {
        if (s.st_mode & (i * 4))
            output[1 + j] = 'r';

        if (s.st_mode & (i * 2))
            output[2 + j] = 'w';

        if (s.st_mode & i)
            output[3 + j] = 'x';
    }

    puts(output);
    return EXIT_SUCCESS;
}
