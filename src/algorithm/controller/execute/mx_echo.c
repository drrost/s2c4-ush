//
// Created by Karina Barinova on 07.10.2020.
//

#include <ush.h>

static int separator_error(char **parse, int *n, int separator) {
    if (separator == -1) {
        *n = -1;
        mx_strdel(parse);
        mx_printerr("Odd number of quotes.\n");
        return -1;
    }
    return 0;
}

static void escape(int i, char *str, char *parse, int index) {
    if (str[i] == 'a')
        parse[index] = '\a';
    else if (str[i] == 'b')
        parse[index] = '\b';
    else if (str[i] == 't')
        parse[index] = '\t';
    else if (str[i] == 'n')
        parse[index] = '\n';
    else if (str[i] == 'v')
        parse[index] = '\v';
    else if (str[i] == 'f')
        parse[index] = '\f';
    else if (str[i] == 'r')
        parse[index] = '\r';
    else
        parse[index] = str[i];
}

static char *fill_str(char *str, int *n, int flag, bool flag_off) {
    char *parse = mx_strnew(1000);
    int separator = 1;
    int index = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\"' || str[i] == '\'')
            separator *= -1;
        else if (flag == 1 && str[i] == '\\' && separator == -1)
            escape(++i, str, parse, index++);
        else if (str[i] == '\\' && separator == 1)
            parse[index++] = str[++i];
        else if (flag_off)
            parse[index++] = str[i];
        // else {
        //     parse[index++] = str[i];
        // }
    }
    parse[index] = '\0';
    if (separator_error(&parse, n, separator) == -1)
        *n = -1;
    //mx_strdel(&str);
    return parse;
}

static int echo_flag(char *str, int *n) {
    int flag = 1;

    for (int i = 1; i < mx_strlen(str); i++) {
        if (str[i] == 'e' && flag != 2)
            flag = 1;
        else if (str[i] == 'E' || str[i] == 'e')
            flag = 2;
        else if (str[i] == 'n')
            *n = 1;
        else {
            flag = -1;
            break;
        }
    }
    return flag;
}

static char *change(const char *line) {
    char *str = mx_strdup(line);

    for ( int i = 0, j; str[i]; ++i) {
        while (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z')
            && !(str[i] == '\0')) {
            for (j = i; str[j]; ++j) {
                str[j] = str[j + 1];
            }
            str[j] = '\0';
        }
    }
    return str;
}

char *mx_parse_echo(char *line, int *n) {
    int flag = 1;
    char *str = NULL;
    bool flag_off = true;

    if (line[0] == '-' && str == NULL && flag != -1) {
        flag = echo_flag(line, n);
        flag_off = false;
    }
    if (str == NULL && mx_strcmp(line, "") != 0){
        if (mx_strstr(line, "${") != 0) {
            char *env = change(line);
            if (getenv(env) != NULL) {
                str = mx_strdup(mx_getenv(env));
            }
        }
        else
            str = mx_strdup(line);
    }
    else if (mx_strcmp(line, "") != 0) {
        str = mx_realloc(str, strlen(str) + strlen(line) + 2);
        mx_strcat(str, "");
        mx_strcat(str, line);
    }
    if (str != NULL)
        str = fill_str(str, n, flag, flag_off);
    return str;
}

int mx_echo(char *args, int exit_code) {
    int check = 0;

    if (mx_strstr(args, "$?") != 0)
        mx_printint(exit_code);

    char *str = mx_parse_echo(args, &check);

    if (str != NULL)
        mx_printstr(str);
    if (check == 0)
        mx_printstr("\n");
    else if (check == -1)
        return 1;
    //mx_strdel(&str);
    return 0;
}
