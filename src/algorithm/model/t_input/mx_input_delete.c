//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

void mx_input_delete(t_input **instance) {
    t_list *commands = (*instance)->commands;
    while (commands) {
        t_command *command = (t_command *)commands->data;
        mx_command_delete(&command);
        mx_pop_front(&commands);
    }
    mx_strdel(&((*instance)->error_text));
    free(*instance);
    *instance = 0;
}
