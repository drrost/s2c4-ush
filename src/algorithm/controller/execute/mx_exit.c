//
// Created by Karina Barinova on 28.09.2020.
//

#include <ush.h>

int mx_exit(char *line) {
    if (mx_strlen(line) > 0)
        mx_setenv("GLOBAL_EXIT_CODE", line);

    return MX_SHOULD_EXIT;
}
