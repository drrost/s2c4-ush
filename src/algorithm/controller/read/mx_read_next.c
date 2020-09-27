//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

char *mx_read_next() {
    char *line = mx_strnew(128);
    char ch;
    scanf("%2000[^\n]%c", line, &ch);
    return line;
}
