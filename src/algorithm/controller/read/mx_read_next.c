//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

static void handle_key(const char c, t_termstate *state) {
    putchar(c);
    state->line[state->pos] = c;
    state->pos++;

    char *s = mx_itoa(c);
    mx_log_t("Key: ", s);
    mx_strdel(&s);
}

char * mx_read_next() {
    char *str = "cd ~+;''ls -l -a && cd  $(PWD); pwd || cd ; (hello); echo; exit";
    return mx_strdup(str);

    struct termios save;
    struct termios raw;
    tcgetattr(STDIN_FILENO, &save);
    tcgetattr(STDIN_FILENO, &raw);
    cfmakeraw(&raw);
    tcsetattr(STDIN_FILENO, 0, &raw);

    t_termstate *state = mx_termstate_new();
    int c;
    while ((c = getchar()) != 13) {
        if (c == 3 || c == 24 || c == 26)
            break;
        handle_key(c, state);
    }

    tcsetattr(STDIN_FILENO, 0, &save);
    putchar('\n');

    char *line = mx_strdup(state->line);
    mx_termstate_del(&state);
    return line;
}
