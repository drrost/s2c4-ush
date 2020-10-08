//
// Created by Rostyslav Druzhchenko on 06.10.2020.
//

#include <mx_core.h>
#include <ush.h>

void mx_history_delete() {
    t_list *history = *(mx_history_get());
    while (history) {
        mx_strdel(history->data);
        mx_pop_front(&history);
    }
}
