//
// Created by Karina Barinova on 11.10.2020.
//

#include <ush.h>

void mx_printerr_char(char c) {
    char s[2];
    s[0] = c;
    s[1] = '\0';
    mx_printerr(s);
}
