//
// Created by Karina Barinova on 23.10.2020.
//

#include <ush.h>

static void mx_resolution_error(char *var_name) {
    char *msg  = "u$h> can`t resolve '~' bacause ";
    char *msg2 = " var is not set\n";
    mx_printerr(msg);
    mx_printerr(var_name);
    mx_printerr(msg2);
}

static void mx_var_replace(char **arr, char *replace) {
    char *var = mx_getenv(replace);

    if (var == NULL)
        mx_resolution_error(replace);
    else {
        free(arr[0]);
        arr[0] = mx_strdup(var);
    }
}

static int user_exist(char *user) {
    struct passwd *pass;

    while (1) {
        pass = getpwent();
        if (!pass)
            break;
        if (mx_streq(pass->pw_name, user)) {
            endpwent();
            return 1;
        }
    }
    endpwent();
    return 0;
}

char *mx_arr_to_path(char **arr) {
    int i = 1;
    char *new = mx_strdup(arr[0]);
    char *tmp = 0;

    while (arr[i]) {
        tmp = mx_three_join(new,  "/", arr[i]);
        free(new);
        new = mx_strdup(tmp);
        free(tmp);
        i++;
    }
    return new;
}

static void mx_tilda_and_username(char **arr) {
    char *user = mx_substr_retriever(arr[0], 1, mx_strlen(arr[0]));
    int exist = user_exist(user);
    char *str = mx_strdup("/Users/");

    if (exist) {
        str = mx_strjoin(str, user);
        free(arr[0]);
        arr[0] = str;
    }
    free(user);
}

static void tilda_replace(char **split) {
    if (split[0] == NULL)
        return;
    if (mx_streq(split[0], "~"))
        mx_var_replace(split, "HOME");
    else if (mx_streq(split[0], "~+"))
        mx_var_replace(split, "PWD");
    else if (mx_streq(split[0], "~-"))
        mx_var_replace(split, "OLDPWD");
    else if (split[0][0] == '~')
        mx_tilda_and_username(split);
}

void expand_tilda(t_command *command) {
    char **arr = mx_strsplit(command->arguments, ' ');
    char **split;
    int i = 0;

    while (arr[i]) {
        if (arr[i][0] == '~') {
            split = mx_strsplit(arr[i], '/');
            tilda_replace(split);
            free(arr[i]);
            arr[i] = mx_arr_to_path(split);
            mx_del_strarr(&split);
        }
        i++;
    }

    mx_strdel(&(command->arguments));
    command->arguments = mx_str_joined_by(arr, " ");

    mx_del_strarr(&arr);

}
