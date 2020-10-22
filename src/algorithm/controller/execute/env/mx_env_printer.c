//
// Created by Karina Barinova on 22.10.2020.
//

#include <ush.h>

void mx_print_env(void) {
    t_map *env = mx_env_get();
    t_list *list = env->content;
    while (list) {
        t_pair *pair = (t_pair *)list->data;
        mx_printstr(pair->key);
        mx_printstr("=");
        mx_printstr(pair->value);
        mx_printstr("\n");
        list = list->next;
    }
    mx_map_delete(&env);
}

void error_msg(char *option) {
    char *msg  = "env: illegal option "; 
    char *msg1 = "usage: env [-iv] [-P utilpath] [-S string] [-u name]\n";
    char *msg2 = "           [name=value ...] [utility [argument ...]]\n";

    mx_printerr(msg);
    mx_printerr(option);
    mx_printerr("\n");
    mx_printerr(msg1);
    mx_printerr(msg2);
}

void mx_option_requires_an_argument(char *option) {
    char *msg  = "env: option requires an argument -- ";
    char *msg1 = "usage: env [-iv] [-P utilpath] [-S string] [-u name]\n";
    char *msg2 = "           [name=value ...] [utility [argument ...]]\n";

    mx_printerr(msg);
    mx_printerr(option);
    mx_printerr("\n");
    mx_printerr(msg1);
    mx_printerr(msg2);
}

int print_env_without_var(char *var_name) {
    if (mx_get_char_index(var_name, '=') != -1) {
        mx_printerr("env: unsetenv ");
        mx_printerr(var_name);
        mx_printerr(": Invalid argument\n");
        return 1;
    }
    unsetenv(var_name);
    mx_print_env();
    return 0;
}
