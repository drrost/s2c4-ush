//
// Created by Karina Barinova on 08.10.2020.
//

#include <ush.h>

char *mx_clear_str_of_symbols(const char *line) {
    char *str = mx_strdup(line);

    for ( int i = 0, j; str[i]; ++i) {
        while (!(mx_isalpha(str[i])) && !(str[i] == '\0')) {
            for (j = i; str[j]; ++j)
                str[j] = str[j + 1];
            str[j] = '\0';
        }
    }
    return str;
}

int mx_hex(char *str, int *i) {
    char *buf = mx_strnew(3);
    int res = 0;

    res = mx_get_hex_and_oct(buf, str, i);
    free(buf);
    return res;
}

bool mx_print_exit_code(char *s) {
    bool done = false;
    char *str = 0;
    if (mx_streq(s, "$?")) {
        str = mx_strdup(mx_getenv("EXIT_CODE"));
        mx_printstr(str);
        done = true;
        mx_strdel(&str);
    }
    return done;
}


bool mx_regex(char *str, char *regular) {
    regex_t regex;
    int result;

    regcomp(&regex, regular, REG_EXTENDED);
    result = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);
    return result == 0;
}

int mx_get_hex_and_oct(char *buf, char *str, int *i) {
    if (str[*i + 1] == 'x' && mx_regex(str + *i + 2, "^[0-9a-fA-F].*$")) {
        *i += 2;
        buf[0] = str[*i];
        buf[1] = str[(*i) + 1];
        (*i)++;
        return (int)strtol(buf, NULL, 16);
    }
    else if (str[*i + 1] == '0' && mx_regex(str + *i + 2, "^[0-7]{2,3}.*$")) {
        *i += 2;
        buf[0] = str[*i];
        buf[1] = str[(*i) + 1];
        if (str[*i + 2] >= '0' && str[*i + 2] <= '7') {
            buf[2] = str[*i + 2];
            (*i)++;
        }
        (*i)++;
        return (int)strtol(buf, NULL, 8);
    }
    return -1;
}


