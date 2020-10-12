//
// Created by Rostyslav Druzhchenko on 12.10.2020.
//

#include <ush.h>

void mx_history_add_to_file(char *line) {
    char *file_name = mx_history_file();

    int fd = open(file_name, O_WRONLY | O_CREAT  | O_APPEND, 0700);
    int len = mx_strlen(line);

    write(fd, line, len);
    write(fd, "\n", 1);

    mx_strdel(&file_name);
    close(fd);
}
