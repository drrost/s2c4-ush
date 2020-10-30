//
// Created by Karina Barinova on 07.10.2020.
//

#include <ush.h>


static int print_echo_e(char *str) {
    char buf;

    if (str[0] == '$' || (str[0] == '$' & str[1] == '{'))
        return 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (buf == '\\') {
            buf = 0;
            continue;
        }
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
        if (buf == 34 || buf == 39) //TO DO: may be needed to rethink the fix (case echo -n "\a")
            continue;
        else
            write(1, &buf, 1);
    }
    return 1;
}

bool print_env_var(char *s) {
    bool done = false;
    char *str = 0;

    if (mx_strstr(s, "$") != 0) {
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

static void print_e(int i, char *flags, char **arr) {
    int err = 1;
    int j = 0;
    
    if (arr[j][0] == '-' && mx_strcmp(arr[j], "-E") && mx_strcmp(arr[j], "-e") && mx_strcmp(arr[j], "-n"))
        mx_printstr(arr[i]);

    for (i = i + 1; arr[i]; i++) {
        if(!print_env_var(arr[i]) && !mx_print_exit_code(arr[i]) && arr[i][0] != '\'')
            err = print_echo_e(arr[i]);
        if (arr[i + 1] && err)
            write(1, " ", 1);
    }
    if (flags[0] != 'n' && err)
        write(1, "\n", 1);
}

static void print_no_args(char **arr) {
    int err = 1;

    for (int i = 0; arr[i]; i++) {
        if(!print_env_var(arr[i]) && !mx_print_exit_code(arr[i])) {
            err = print_echo_e(arr[i]);
        }
        if (arr[i + 1]) {
            if (err) {
                write(1, " ", 1);
            }
        }   
        else {
            write(1, "\n", 1);
        }
    }
}

char *replace_str(char *s) {
    int len = mx_strlen(s);
    int j = 0;
    for (int i = 0; i < len; i ++) {
        if (s[i] != '"' && s[i] != '\\') { 
            s[j++] = s[i];
        } else if (s[i+1] == '"' && s[i] == '\\') { 
            s[j++] = '"';
        } else if (s[i+1] != '"' && s[i] == '\\') { 
            s[j++] = '\\';
        }
    }
    if(j > 0) 
        s[j] = 0;
    return s;
}

int mx_echo(char *args) {
    char *args_w = 0;
    if (mx_streq(args, "$?"))
        args_w = mx_strdup(mx_getenv("EXIT_CODE"));
    else
        args_w = mx_strdup(args);

    if (mx_strlen(args_w) > 0) {
        int i = 0;
        char **arr = mx_strsplit(args_w, ' ');
        char *flags = mx_checkflags_echo(arr, &i);

        if (flags[1] == 'E') {
            for (i = i + 1; arr[i]; i++) {
                arr[i] = replace_str(arr[i]);
                if(!print_env_var(arr[i]) && !mx_print_exit_code(arr[i]))
                    if (!mx_streq(arr[i], """"))
                        write(1, arr[i], mx_strlen(arr[i]));
                if (arr[i + 1])
                    write(1, " ", 1);
            }
            if (flags[0] != 'n')
                write(1, "\n", 1);
        }
        else if(arr[0][0] != '-')
            print_no_args(arr);
        else {
            print_e(i, flags, arr);
        }
        free(flags);
        mx_del_strarr(&arr);
    }
    else
        mx_printstr("\n");

    mx_strdel(&args_w);
    return 0;
}
