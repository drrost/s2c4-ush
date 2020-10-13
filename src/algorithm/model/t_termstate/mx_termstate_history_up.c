//
// Created by Rostyslav Druzhchenko on 13.10.2020.
//

#include <algorithm.h>

void mx_termstate_history_up(t_termstate *this) {
    if (this->history_state.pos == 0)
        return;

    if (this->history_state.pos == this->history_state.size - 1) {
        mx_strdel(&(this->backup_line));
        this->backup_line = this->line;
        this->line = 0;
    }

    t_list *node = mx_list_at(this->history_state.list,
                              this->history_state.pos);
    char *s = (char *)node->data;
    mx_strdel(&(this->line));
    this->line = mx_strdup(s);
    this->cursor_pos = mx_strlen(this->line);

    this->history_state.pos--;
}
