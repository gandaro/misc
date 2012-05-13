/* vim: set cin et sw=4 ts=4: */

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
    int group, offset, file;
    struct stat s;
    char output[10] = "----------";

    if (argc < 2)
        errexit("Usage: fprm FILE...");

    for (file = 1; file < argc; file++) {
        if (stat(argv[file], &s) == -1)
            errexit("fprm: stat() failed");

        if (S_ISDIR(s.st_mode))
            output[0] = 'd';

        for (group = 0100, offset = 0; group >= 1; group /= 010, offset += 3) {
            if (s.st_mode & (group * 4))
                output[1 + offset] = 'r';

            if (s.st_mode & (group * 2))
                output[2 + offset] = 'w';

            if (s.st_mode & group)
                output[3 + offset] = 'x';
        }

        /* print file name, if there is more than one file specified */
        if (argc > 2)
            printf("%s: ", argv[file]);

        puts(output);
    }

    return EXIT_SUCCESS;
}
