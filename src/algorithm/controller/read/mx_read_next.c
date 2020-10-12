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

static bool is_arrow_right(const char *s) {
    return s[0] == 27 && s[1] == 91 && s[2] == 67;
}

static bool is_arrow_left(const char *s) {
    return s[0] == 27 && s[1] == 91 && s[2] == 68;
}

static void log_esc_sequence(const char *input_buff) {
    if (is_arrow_up(input_buff))
        mx_log_t("up arrow", "");
    else if (is_arrow_down(input_buff))
        mx_log_t("down arrow", "");
    else if (is_arrow_right(input_buff))
        mx_log_t("right arrow", "");
    else if (is_arrow_left(input_buff))
        mx_log_t("left arrow", "");
    else
        mx_log_t("unknown sequence", "");
}

static bool is_esc_sequence_part(char c, char **complete) {
    static char input_buff[4];
    static int buff_idx = 0;
    if (buff_idx == 0)
        mx_memset(input_buff, 0, 4);
    if ((buff_idx == 0 && c == 27) ||
        (buff_idx == 1 && c == 91)) {
        input_buff[buff_idx] = c;
        buff_idx++;
        return true;
    }
    else if (buff_idx == 2) {
        input_buff[buff_idx] = c;
        buff_idx = 0;
        *complete = input_buff;
        return false;
    }
    else
        buff_idx = 0;
    return false;
}

static void clear_current_line() {
    putchar('\r');
    int win_width = mx_get_window_width();
    for (int i = 0; i < win_width; i++)
        putchar(' ');
    putchar('\r');
}

static void print_tricky_str(char *s) {
    int len = mx_strlen(s);
    for (int i = 0; i < len; i++) {
        putchar(s[i]);
    }
}

static void print_prompt() {
    print_tricky_str("u$l> ");
}

static void handle_backspace(t_termstate *state) {
    state->line[state->cursor_pos - 1] = 0;
    clear_current_line();
    print_prompt();
    print_tricky_str(state->line);

    state->cursor_pos--;
}

static void handle_key(const char c, t_termstate *state) {
    char *complete = 0;
    if (is_esc_sequence_part(c, &complete))
        return;

    if (complete) {
        log_esc_sequence(complete);
        return;
    }

    if (c == 127) {
        handle_backspace(state);
        return;
    }

    putchar(c);
    state->line[state->cursor_pos] = c;
    state->cursor_pos++;

    char *s = mx_itoa(c);
    mx_log_t("Key: ", s);
    mx_strdel(&s);
}

char *mx_read_next() {
    print_prompt();
//    char *str = "cd ~;''ls -la && pwd; pwd || cd ; (hello); echo; exit";
//    static int count = 0;
//    char *str_1 = 0;

    struct termios save;
    struct termios raw;
    tcgetattr(STDIN_FILENO, &save);
    tcgetattr(STDIN_FILENO, &raw);
    cfmakeraw(&raw);
    tcsetattr(STDIN_FILENO, 0, &raw);

    t_termstate *state = mx_termstate_new();
    int c;
    while ((c = getchar()) != 13) {
        if (c == 3 || c == 24 || c == 26) {
            mx_strcpy(state->line, "exit");
            break;
        }
        handle_key(c, state);
    }

    tcsetattr(STDIN_FILENO, 0, &save);
    putchar('\n');

    char *line = mx_strdup(state->line);
    mx_termstate_del(&state);

    mx_history_add_to_list(mx_strdup(line));
    mx_history_add_to_file(line);

    return line;
}
