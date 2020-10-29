//
// Created by Karina Barinova on 15.10.2020.
//

#include <ush.h>

int mx_file_exist(char *path) {
    struct stat st;
    int flag = 0;

    if ((lstat(path, &st) != -1))
        flag = 1;
    return flag;
}

static int is_comm_rw(char *str) {
    char reserved_words[][6] = {"!", "{", "}", "time", "export"};

    for (int i = 0; i < 5; i++) {
        if (mx_strcmp(str, reserved_words[i]) == 0)
            return 1;
    }
    return -1;
}

static char *check_in_path(char *command, char **path) {
    char *command_p = NULL;

    for (int i = 0; i < mx_arr_size(path); i++) {
        command_p = mx_strnew(mx_strlen(command) + mx_strlen(path[i]) + 1);
        mx_strcpy(command_p, path[i]);
        command_p = mx_strcat(command_p, "/");
        command_p = mx_strcat(command_p, command);
        if (mx_file_exist(command_p))
            break;
        mx_strdel(&command_p);
    }
    return command_p;
}


static void mx_free_void_arr(void **arr, int lines) {
    if (arr != NULL) {
        for (int i = 0; i < lines; i++) {
            free(arr[i]);
            arr[i] = NULL;
        }
        free(arr);
        arr = NULL;
    }
}

char *mx_command_in_path(char *comm, char *str_path) {
    char **path = NULL;
    char *command_p = NULL;
    int paths = 0;
    int i = 0;

    if (str_path != NULL) {
        path = mx_strsplit(str_path, ':');
        paths = mx_arr_size(path);
        if (mx_strstr(str_path, "PATH=") != NULL) {
            for (; i < mx_strlen(path[0]) - 5; i++)
                path[0][i] = path[0][i + 5];
            path[0][i] = '\0';
        }
        if (mx_strcmp(comm, "/") != 0 && mx_get_char_index(comm, '/') == -1)
            command_p = check_in_path(comm, path);
        mx_free_void_arr((void **) path, paths);
    }
    if (command_p == NULL)
        command_p = mx_strdup(comm);
    return command_p;
}

static void check_builtin(char *str, int *ret_flag, int flag) {
    char *tmp = NULL;

    tmp = mx_command_in_path(str, mx_getenv("PATH"));
    if (mx_is_builtin(tmp) != 0) {
        mx_printstr(str);
        mx_printstr(": shell built-in command\n");
        if (flag == 2 && mx_strcmp(tmp, str) != 0)
            printf("%s\n", tmp);
    }
    else if (mx_strcmp(tmp, str) != 0) {
            printf("%s\n", tmp);
    }
    else
        *ret_flag = 1;
    mx_strdel(&tmp);
}


void mx_check_command(char *str, int *ret_flag, int flag) {
    char **path = NULL;

    if (is_comm_rw(str) == 1) {
        mx_printstr(str);
        mx_printstr(": shell reserved word\n");
    }
    else if (mx_get_char_index(str, '/') != -1) {
        path = mx_strsplit(mx_getenv("PATH"), ':');
        for (int y = 0; y < mx_arr_size(path); y++) {
            if (mx_get_substr_index(str, path[y]) != -1
                && mx_file_exist(str)) {
                if (flag != 1)
                    printf("%s\n", str);
                *ret_flag = 0;
                break;
            }
            *ret_flag = 1;
        }
        mx_free_void_arr((void**)path, mx_arr_size(path));
    }
    else
        check_builtin(str, ret_flag, flag);
}
