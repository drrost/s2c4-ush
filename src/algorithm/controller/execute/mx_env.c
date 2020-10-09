//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <ush.h>

void mx_env(const char *args) {
    args++;

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
}
