//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <ush.h>

extern char **environ;

void mx_env(const char *args) {
    args++;
    for (char **env = environ; *env; ++env)
        mx_printline(*env);
}
