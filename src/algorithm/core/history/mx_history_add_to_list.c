//
// Created by Rostyslav Druzhchenko on 06.10.2020.
//

#include <ush.h>

void mx_history_add_to_list(char *line) {
    mx_push_back(mx_history_get(), line);
}
