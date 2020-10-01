//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

static void handle_key(const char c) {
    putchar(c);

    char *s = mx_itoa(c);
    mx_log_t("Key: ", s);
    mx_strdel(&s);
}

char *mx_read_next() {
    struct termios save;
    struct termios raw;
    tcgetattr(STDIN_FILENO, &save);
    tcgetattr(STDIN_FILENO, &raw);

    cfmakeraw(&raw);
    tcsetattr(STDIN_FILENO, 0, &raw);

    int c;
    while ((c = getchar()) != '.') {
        if (c == 3 || c == 24 || c == 26)
            break;
        handle_key(c);
    }

    tcsetattr(STDIN_FILENO, 0, &save);

    return mx_strdup("exit");
}
