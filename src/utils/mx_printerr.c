//
// Created by Karina Barinova on 25.09.2020.
//

#include <ush.h>
#include <mx_log.h>

void mx_printerr(const char *str) {
    write(STDERR_FILENO, str, mx_strlen(str));
}
