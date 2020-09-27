//
// Created by Karina Barinova on 25.09.2020.
//

#include <ush.h>
#include <unistd.h>

void mx_printerr(const char *str) {
    mx_log_e("", str);
    write(STDERR_FILENO, str, mx_strlen(str));
}
