//
// Created by Rostyslav Druzhchenko on 13.10.2020.
//

#include <algorithm.h>

void mx_termstate_history_down(t_termstate *this) {
    if (this->history_state.pos < this->history_state.size)
        this->history_state.pos++;

    if (this->history_state.pos >= this->history_state.size) {
        mx_strdel(&(this->line));
        if (this->backup_line)
            this->line = mx_strdup(this->backup_line);
        else
            this->line = mx_strdup("");
        mx_strdel(&(this->backup_line));
        this->cursor_pos = 0;
        return;
    }

    t_list *node = mx_list_at(this->history_state.list,
                              this->history_state.pos);
    char *s = (char *)node->data;
    mx_strdel(&(this->line));
    this->line = mx_strdup(s);
    this->cursor_pos = mx_strlen(this->line);
}
