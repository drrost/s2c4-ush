//
// Created by Rostyslav Druzhchenko on 26.10.2020.
//

#include <private/mx_parse_private.h>

void mx_get_command_node(t_list **chain, char *trim,
                         bool has_or, bool has_and) {
    t_command *command = mx_command_new();
    int trim_len = mx_strlen(trim);
    int command_len = trim_len;
    int arg_len = 0;
    char *s = 0;

    if ((s = mx_strstr(trim, " ")) != 0) {
        command->arguments = mx_strdup(s + 1);
        arg_len = mx_strlen(s);
        command_len = trim_len - arg_len;
    }
    else
        command->arguments = mx_strdup("");

    command->name = mx_strndup(trim, command_len);
    if (has_or) {
        command->has_or = has_or;
        command->has_and = false;
    }
    else {
        command->has_and = has_and;
        command->has_or = false;
    }
    if (!has_and && !has_or)
        command->is_last_in_sequesce = true;
    else
        command->is_last_in_sequesce = false;

    mx_push_front(chain, command);

    mx_substitute_runnable(chain, command, "$(", ')');
    mx_substitute_runnable(chain, command, "`", '`');
}
