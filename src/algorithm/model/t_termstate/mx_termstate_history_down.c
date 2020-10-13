//
// Created by Rostyslav Druzhchenko on 13.10.2020.
//

#include <algorithm.h>

#include <mx_log.h>

void mx_termstate_history_down(t_termstate *this) {
    char *pos = mx_itoa(this->history_state.pos);
    mx_log_t("pos", pos);
    mx_strdel(&pos);

    char *size = mx_itoa(this->history_state.size);
    mx_log_t("size", size);
    mx_strdel(&size);

    if (this->history_state.pos >= this->history_state.size - 1)
        return;

    if (this->history_state.pos == this->history_state.size - 2) {
        mx_strdel(&(this->line));
        this->line = mx_strdup(this->backup_line);
        mx_strdel(&(this->backup_line));
        this->history_state.pos++;
        return;
    }

    t_list *node = mx_list_at(this->history_state.list,
                              this->history_state.pos);
    char *s = (char *)node->data;
    mx_strdel(&(this->line));
    this->line = mx_strdup(s);
    this->cursor_pos = mx_strlen(this->line);

    this->history_state.pos++;
}
