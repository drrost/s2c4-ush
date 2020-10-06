//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

void mx_input_delete(t_input **instance) {
    mx_strdel(&((*instance)->command));
    t_list *commands = (*instance)->commands;
    while (commands) {
        t_command *command = (t_command *)commands->data;
        mx_command_delete(&command);
        mx_pop_front(&commands);
    }
    free(*instance);
    *instance = 0;
}
