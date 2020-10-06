//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

static bool is_arrow_up(const char *s) {
    return s[0] == 27 && s[1] == 91 && s[2] == 65;
}

static bool is_arrow_down(const char *s) {
    return s[0] == 27 && s[1] == 91 && s[2] == 66;
}

static void handle_key(const char c, t_termstate *state) {
    static char input_buff[4];
    static int buff_idx = 0;
    if (buff_idx == 0)
        mx_memset(input_buff, 0, 4);

    if (buff_idx == 0 && c == 27) {
        input_buff[buff_idx] = c;
        buff_idx++;
        return;
    }
    else if (buff_idx == 1 && c == 91) {
        input_buff[buff_idx] = c;
        buff_idx++;
        return;
    }
    else if (buff_idx == 2) {
        input_buff[buff_idx] = c;
        buff_idx++;
        if (is_arrow_up(input_buff))
            mx_log_t("up arrow", "");
        if (is_arrow_down(input_buff))
            mx_log_t("down arrow", "");
        buff_idx = 0;
        return;
    }
    else {
        buff_idx = 0;
    }

    putchar(c);
    state->line[state->pos] = c;
    state->pos++;

    char *s = mx_itoa(c);
    mx_log_t("Key: ", s);
    mx_strdel(&s);
}

char * mx_read_next() {
    char *str = "cd ~;''ls -la && pwd; pwd || cd ; (hello); echo; exit";
    return mx_strdup(str);

//    struct termios save;
//    struct termios raw;
//    tcgetattr(STDIN_FILENO, &save);
//    tcgetattr(STDIN_FILENO, &raw);
//    cfmakeraw(&raw);
//    tcsetattr(STDIN_FILENO, 0, &raw);
//
//    t_termstate *state = mx_termstate_new();
//    int c;
//    while ((c = getchar()) != 13) {
//        if (c == 3 || c == 24 || c == 26)
//            break;
//        handle_key(c, state);
//    }
//
//    tcsetattr(STDIN_FILENO, 0, &save);
//    putchar('\n');
//
//    char *line = mx_strdup(state->line);
//    mx_termstate_del(&state);
//    return line;
}
