//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#ifndef INC_04_USH_MX_CORE_H
#define INC_04_USH_MX_CORE_H

#include <mx_map.h>
#include <stdlib.h>
#include <stdbool.h>

// Environment variables
//
t_map *mx_env_get();
char *mx_getenv(const char *s);
void mx_setenv(const char *key, const char *value);

// History
//
t_list **mx_history_get();
void mx_history_add_to_list(char *line);
void mx_history_add_to_file(char *line);
void mx_history_delete();
char *mx_history_file();

// Core
//
void mx_core_init();
void mx_core_clean();

#endif //INC_04_USH_MX_CORE_H
