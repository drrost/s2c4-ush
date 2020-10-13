//
// Created by Karina Barinova on 07.10.2020.
//

#include <ush.h>


static int print_echo_e(char *str) {
    char buf;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\\' && mx_regex(str + i + 1, "^(x[0-9a-fA-F]{2}.*)|(0[0-7]{2,3}.*)$")) {
            buf = mx_hex(str, &i);
        }
        else if (str[i] == '\\' && str[i + 1] == '\\')
            buf = '\\';
        else if (str[i] == '\\' && str[i + 1] == '0' && ++i > 0)
            buf = '\0';
        else if ((buf = mx_print_echo_d(&str[i], &i)) != -1);
        else if (str[i] == '\\' && str[i + 1] == 'c' && ++i > 0)
            return 0;
        else
            buf = str[i];
        if (buf == 34) //TO DO: may be needed to rethink the fix (case echo -n "\a")
            continue;
        else
            write(1, &buf, 1);
    }
    return 1;
}

bool print_env_var(char *s) {
    bool done = false;
    char *str = 0;
    if (mx_strstr(s, "${") != 0) {
        char *env = mx_clear_str_of_symbols(s);
        if (mx_getenv(env) != NULL) {
            str = mx_strdup(mx_getenv(env));
            mx_printstr(str);
            done = true;
            mx_strdel(&str);
        }
        mx_strdel(&env);
    }
    return done;
}


static void print_e(int i, char *flags, char **arr, int exit_code) {
    int err = 1;

    for (i = i + 1; arr[i]; i++) {
        if(!print_env_var(arr[i]) && !mx_print_exit_code(exit_code, arr[i]))
            err = print_echo_e(arr[i]);
        if (arr[i + 1] && err)
            write(1, " ", 1);
    }
    if (flags[0] != 'n' && err)
        write(1, "\n", 1);
}

static void print_no_args(char **arr, int exit_code) {
    int err = 1;

    for (int i = 0; arr[i]; i++) {
        if(!print_env_var(arr[i]) && !mx_print_exit_code(exit_code, arr[i]))
            err = print_echo_e(arr[i]);
        if (arr[i + 1] && err) 
            write(1, " ", 1);
        else
            write(1, "\n", 1);
    }
}

int mx_echo(char *args, int exit_code) {
    if (mx_strlen(args) > 0) {
        int i = 0;
        char **arr = mx_strsplit(args, ' ');
        char *flags = mx_checkflags_echo(arr, &i);

        if (flags[1] == 'E') {
            for (i = i + 1; arr[i]; i++) {
                if(!print_env_var(arr[i]) && !mx_print_exit_code(exit_code, arr[i]) && !mx_streq(arr[i], "\"\""))
                    write(1, arr[i], mx_strlen(arr[i]));
                if (arr[i + 1])
                    write(1, " ", 1);
            }
            if (flags[0] != 'n')
                write(1, "\n", 1);
        }
        else if(arr[0][0] != '-')
            print_no_args(arr, exit_code);
        else {
            print_e(i, flags, arr, exit_code);
        }
        free(flags);
        mx_del_strarr(&arr);
        return 0;
    }
    else
        mx_printstr("\n");
    return 0;
}
