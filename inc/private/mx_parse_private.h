//
// Created by Rostyslav Druzhchenko on 26.10.2020.
//

#ifndef INC_04_USH_MX_PARSE_PRIVATE_H
#define INC_04_USH_MX_PARSE_PRIVATE_H

#include <ush.h>

void mx_substitute_runnable(t_list **chain, t_command *command,
                            char *from, char to);
void mx_get_command_node(t_list **chain, char *trim,
                         bool has_or, bool has_and);

#endif //INC_04_USH_MX_PARSE_PRIVATE_H
