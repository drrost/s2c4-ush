//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>

static void print_debug(const char *line) {
    // open file
    FILE *file = fopen("./log.txt", "a+");

    // write time
    // write level

    // write the line
    fprintf(file, "%s\n", line);

    // close file
    fclose(file);
}

char *current_time() {
    time_t raw_time;
    struct tm *time_info;

    time(&raw_time);
    time_info = localtime(&raw_time);

    static char time_str[128];
    sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d",
            time_info->tm_year + 1900, time_info->tm_mon + 1,
            time_info->tm_mday, time_info->tm_hour,
            time_info->tm_min, time_info->tm_sec);

    return mx_strdup(time_str);
}

void mx_log_d(const char *subject, const char *details) {
    char *to_print = current_time();
    char *old = 0;

    old = to_print;
    to_print = mx_strjoin(to_print, " ");
    mx_strdel(&old);

    old = to_print;
    to_print = mx_strjoin(to_print, subject);
    mx_strdel(&old);

    if (mx_strlen(details)) {
        old = to_print;
        to_print = mx_strjoin(to_print, " - ");
        mx_strdel(&old);

        to_print = mx_strjoin(to_print, details);
        mx_strdel(&old);
    }

    print_debug(to_print);
    mx_strdel(&to_print);
}
