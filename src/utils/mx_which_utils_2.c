//
// Created by Karina Barinova on 15.10.2020.
//

#include <ush.h>

static int is_built(char *command) {
    if (mx_strcmp("cd", command) == 0)
        return 1;
    if (mx_strcmp("pwd", command) == 0)
        return 2;
    if (mx_strcmp("echo", command) == 0)
        return 9;
    return 0;
}

int mx_is_builtin(char *command) {
    int num = 0;
    char builtins[][20] = {"/usr/bin/cd", "/bin/pwd",
                           "ush", "export", "unset", "exit",
                           "/usr/bin/which", "/bin/echo", "/usr/bin/false", 
                           "/usr/bin/fg", "/bin/kill", "set"};

    for (int i = 0; i < mx_strlen(command); i++)
        command[i] = (char)mx_tolower(command[i]);
    if ((num = is_built(command)) == 0) {
        for (int i = 0; i < 11; i++) {
            if (mx_strcmp(builtins[i], command) == 0) {
                num = i + 1;
            }
        }
    }
    return num;
}
