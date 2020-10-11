//
// Created by Rostyslav Druzhchenko on 06.10.2020.
//

#include <ush.h>

t_list **mx_history_get() {
    static t_list *history = 0;
    return &history;
}
