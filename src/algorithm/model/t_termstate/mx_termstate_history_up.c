//
// Created by Rostyslav Druzhchenko on 13.10.2020.
//

#include <algorithm.h>

void mx_termstate_history_up(t_termstate *this) {
    if (this->history_state.pos > 0)
        this->history_state.pos--;
    else
        return;

    t_list *node = mx_list_at(this->history_state.list,
                              this->history_state.pos);
    if (node == 0) {
        mx_strdel(&(this->line));
        this->line = mx_strdup("");
        return;
    }

    char *s = (char *)node->data;
    mx_strdel(&(this->line));
    this->line = mx_strdup(s);
    this->cursor_pos = mx_strlen(this->line);
}
