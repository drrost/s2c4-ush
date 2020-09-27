//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>

void print_debug(const char *line) {
    // open file
    FILE *file = fopen("./log.txt", "a+");

    // write time
    // write level

    // write the line
    fprintf(file, "%s\n", line);

    // close file
    fclose(file);
}

void mx_print_debug(const char *subject, const char *details) {
    char *to_print = 0;

    if (mx_strlen(details)) {
        to_print = mx_strjoin(subject, ": ");
        char *old = to_print;
        to_print = mx_strjoin(to_print, details);
        mx_strdel(&old);
        print_debug(to_print);
        mx_strdel(&to_print);
    }
    else
        print_debug(subject);
}
