//
// Created by Rostyslav Druzhchenko on 06.10.2020.
//

#include <ush.h>

void mx_history_delete() {
    t_list *history = *(mx_get_history());
    while (history) {
        mx_strdel(history->data);
        mx_pop_front(&history);
    }
}
