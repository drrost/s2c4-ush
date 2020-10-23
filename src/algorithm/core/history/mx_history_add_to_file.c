//
// Created by Rostyslav Druzhchenko on 12.10.2020.
//

#include <ush.h>

void mx_history_add_to_file(char *line) {
    if (line == 0 || mx_strlen(line) == 0)
        return;

    char *trimmed = mx_strtrim(line);
    char *file_name = mx_history_file();

    int fd = open(file_name, O_WRONLY | O_CREAT  | O_APPEND, 0700);
    int len = mx_strlen(trimmed);

    write(fd, trimmed, len);
    write(fd, "\n", 1);

    mx_strdel(&file_name);
    close(fd);

    mx_strdel(&trimmed);
}
