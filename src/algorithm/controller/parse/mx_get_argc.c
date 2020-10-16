#include <ush.h>

char *mx_get_args(char *str) {
    char *pointer = str;
    char *args;
    while (*pointer != ' ' && *pointer != '\0')
        pointer++;

    if (*pointer != '\0') {
        pointer++;
        args = (char *)malloc(sizeof(char) * (mx_strlen(pointer) + 1));
        return mx_strncpy(args, pointer, mx_strlen(pointer) + 1);
    }
    else
        return mx_strdup("");
}
