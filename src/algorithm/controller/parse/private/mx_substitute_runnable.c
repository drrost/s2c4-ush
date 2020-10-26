//
// Created by Rostyslav Druzhchenko on 26.10.2020.
//

#include <private/mx_parse_private.h>

void mx_substitute_runnable(t_list **chain, t_command *command,
                            char *from, char to) {
    int idx_start = mx_strstr_idx(command->arguments, from);
    int idx_end = mx_get_char_index_r(command->arguments, to);

    if (idx_start >= 0 && idx_end >= 0 && idx_end > idx_start) {

        int prefix_len = mx_strlen(from);
        char *new_line = mx_strndup(
            command->arguments + idx_start + prefix_len,
            idx_end - idx_start - prefix_len);
        mx_get_command_node(chain, new_line, false, false);
        t_command *prev_command = (t_command *)((*chain)->data);
        prev_command->subs_set.pass_out_to_next = true;
        mx_strdel(&new_line);

        char *substituted = mx_strndup(
            command->arguments + idx_start, idx_end - idx_start + 1);
        mx_str_replace_p(
            &(command->arguments), substituted, MX_RUN_SUBSTITUTION);
        mx_strdel(&substituted);
    }
}
