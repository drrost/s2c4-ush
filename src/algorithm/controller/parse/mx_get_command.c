#include "../inc/ush.h"
#include <stdlib.h>

char *mx_get_command(char *str) {
    int i = 0;
    char *command;
    for (; str[i] != ' ' && str[i] != '\0'; i++);
    command = (char *) malloc(sizeof(char) * (i + 1));
    //system ("leaks -q ush"); TODO 6 liks
    return mx_strncpy(command, str, i + 1);
}
