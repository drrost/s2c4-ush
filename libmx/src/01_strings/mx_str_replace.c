//
// Created by Rostyslav Druzhchenko on 16.10.2020.
//

#include <libmx.h>
#include <string.h>

char *
mx_str_replace(char *target, const char *needle, const char *replacement) {
    int len = mx_strlen(target);
    char *buffer = mx_strnew(len * 2); // Should be enough for the beginning
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);

    while (1) {
        const char *p = strstr(tmp, needle);
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;
        tmp = p + needle_len;
    }
    return buffer;
}
