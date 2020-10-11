//
// Created by Rostyslav Druzhchenko on 09.10.2020.
//

#include <ush.h>

static int validate_input(char flag, const char *dir) {
    const char *flags = "sP-";
    if (!(flag == 0 || mx_get_char_index(flags, flag) >= 0)) {
        mx_printerr("cd: string not in pwd: -");
        mx_printerr_char(flag);
        mx_printerr("\n");
    }

    // cd Makefile cd: not a directory: Makefile
    // cd ddd - > cd: no such file or directory: ddd
    // cd /.fseventsd -> cd: permission denied: /.fseventsd

    // cd . . -> cd: string not in pwd:

    int exit_code = 0;
    t_path *path = mx_path_new(dir);

    if (path->exists(path) == false) {
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(path->p);
        mx_printerr("\n");
        exit_code = 1;
    }

    mx_path_del(&path);
    return exit_code;
}

static void trace_log(char flag, char *dir) {
    char log_str[1024];
    if (flag != 0)
        sprintf(log_str, "flag: \"-%c\", dir: \"%s\"", flag, dir);
    else
        sprintf(log_str, "flag: \"\", dir: \"%s\"", dir);
    mx_log_t("cd arguments: ", log_str);
}

static char *get_home_dir() {
    return mx_getenv("HOME");
}

static void parse_arguments(const char *line, char *flag, char **dir) {
    char **arr = mx_strsplit(line, ' ');
    int size = mx_arr_size(arr);
    char *home_dir = get_home_dir();

    if (size > 0 && arr[0][0] == '-')
        *flag = mx_strlen(arr[0]) == 1 ? '-' : arr[0][1];

    if (size == 0)
        *dir = mx_strdup(home_dir);
    else if (size == 1)
        *dir = arr[0][0] == '-' ? mx_strdup(home_dir) : mx_strdup(arr[0]);
    else // size == 2
        *dir = mx_strdup(arr[1]);

    trace_log(*flag, *dir);

    mx_del_strarr(&arr);
}

int mx_cd(const char *line) {
    char flag = 0;
    char *dir = 0;
    parse_arguments(line, &flag, &dir);

    validate_input(flag, dir);

    mx_strdel(&dir);
    return 0;
}
