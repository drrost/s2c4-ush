//
// Created by Karina Barinova on 07.10.2020.
//

#include <ush.h>
#include <mx_core.h>

static void mx_not_found(char *str) {
    mx_printerr(str);
    mx_printerr(" not found\n");
}

static int flag_parse(char **command, bool *flag) {
    int i = 1;


    for (; command[i]; i++) {
        if (command[i][0] == '-') {
            for (int j = 1; command[i][j]; j++)
                if (command[i][j] == 'a')
                    flag[0] = 1;
                else if (command[i][j] == 's')
                    flag[1] = 1;
                else {
                    mx_printerr("ush: which: -");
                    mx_printerr_char(command[i][j]);
                    mx_printerr(" invalid option\n");
                    mx_printerr("which: usage: which [-as] program ...\n");
                    return -1;
                }
        }
        else
            break;
    }
    return i;
}

static bool mx_is_command(char *path, bool *flag, int index) {
    struct stat buf;

    if (stat(path, &buf) != -1) {
        if ((buf.st_mode & S_IXUSR) == S_IXUSR) {
            if (!index) {
                if (flag[1])
                    return true;
                mx_printstr(path);
                mx_printstr("\n");
            }
            return true;
        }
    }
    return false;
}

static bool find_in_path(char **ways, char *command, bool *flag) {
    bool a = 0;
    bool trig = 0;

    for (int i = 0; ways[i]; i++) {
        if (mx_get_char_index(command, '/') != -1)
            a = mx_is_command(command, flag, 0);
        else {
            char *path = mx_strjoin(ways[i], "/");
            mx_str_append(&path, command);
            a = mx_is_command(path, flag, 0);
        }
        if (a == 1) {
            if (!flag[0])
                return a;
            else
                trig = 1;
        }
    }
    if (trig == 0)
        mx_not_found(command);
    return a;
}

int mx_which(char *arguments) {
    if (mx_strlen(arguments) > 0) {
        char *path = mx_getenv("PATH");
        bool *flag = (bool *)malloc(sizeof(bool) * 2);
        char **ways = mx_strsplit(path, ':');
        char **arr = mx_strsplit(arguments, ' ');
        int i = flag_parse(arr, flag);

        if (i == -1) {
            return 1;
        }
        for (int j = i - 1; arr[j]; j++) {
            if (arr[j][0] != '-') {
                if (mx_is_built_in(arr[j]) && !flag[1])
                printf("%s: shell built-in command\n", arr[j]);
            }

            if(arr[j][0] != '-') {
                if (!mx_is_built_in(arr[j]) || (mx_is_built_in(arr[j])
                    && flag[0]))
                    find_in_path(ways, arr[j], flag);
            }
        }
        free(flag);
        mx_del_strarr(&ways);
        mx_del_strarr(&arr);
        return 0;
    }
    else {
        mx_printerr("usage: which [-as] program ...\n");
    }
    return 1;
}
