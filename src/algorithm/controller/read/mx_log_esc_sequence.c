//
// Created by Rostyslav Druzhchenko on 12.10.2020.
//

#include <private/mx_read_private.h>
#include <mx_log.h>

void mx_log_esc_sequence(const char *input_buff) {
    if (mx_is_arrow_up(input_buff))
        mx_log_t("up arrow", "");
    else if (mx_is_arrow_down(input_buff))
        mx_log_t("down arrow", "");
    else if (mx_is_arrow_right(input_buff))
        mx_log_t("right arrow", "");
    else if (mx_is_arrow_left(input_buff))
        mx_log_t("left arrow", "");
    else
        mx_log_t("unknown sequence", "");
}
