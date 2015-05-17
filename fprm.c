/* vim: set cin et sw=4 ts=4: */

/*
 *  fprm - print file permissions similar to `ls'
 *  Copyright (C) 2012-2015  Jakob Kramer <jakob.kramer@gmx.de>
 *
 *  This is free and unencumbered software released into the public domain.
 *
 *  Anyone is free to copy, modify, publish, use, compile, sell, or
 *  distribute this software, either in source code form or as a compiled
 *  binary, for any purpose, commercial or non-commercial, and by any
 *  means.
 *
 *  In jurisdictions that recognize copyright laws, the author or authors
 *  of this software dedicate any and all copyright interest in the
 *  software to the public domain. We make this dedication for the benefit
 *  of the public at large and to the detriment of our heirs and
 *  successors. We intend this dedication to be an overt act of
 *  relinquishment in perpetuity of all present and future rights to this
 *  software under copyright law.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 *  For more information, please refer to <http://unlicense.org/>
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
    char output[11] = "----------";

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
