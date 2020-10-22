//
// Created by Karina Barinova on 22.10.2020.
//

#include <ush.h>

static char *search(char **pathes, char *external_name) {
    char *found_path;
    struct dirent *entry;
    int i = 0;
    DIR *dir;
    while(pathes[i]) {
        dir = opendir(pathes[i]);
        if (dir == NULL)
            free(dir);
        else {
            while((entry = readdir(dir)) != NULL) {
                if (mx_strcmp(external_name,  entry->d_name) == 0) {
                    found_path = mx_three_join(pathes[i], "/", external_name);
                    closedir(dir);
                    return found_path;
                }      
            }
            closedir(dir);
        }
        i++;
    }
    return NULL;
}
char *mx_find_external_storage_path(char *external_name, char *path) {
    char **pathes;
    char *found_path;
    if (path == NULL)
        return NULL;
    pathes = mx_strsplit(path, ':');
    if (pathes == NULL) {
        mx_del_strarr(&pathes);
        return NULL;
    }
    found_path = search(pathes, external_name);
    mx_del_strarr(&pathes);
    return found_path;
}

static int err_helper(char *buf, int status, int err) {
    errno = err;

    switch (status) {
        case 1:
            mx_printerr(buf);
            mx_printerr(": No such file or directory\n");
            free(buf);
            return 127;
        case 2:
            perror(buf);
            free(buf);
            return 127;
        case 3:
            errno = 21;
            perror(buf);
            free(buf);
            return 126;
    }
    return 0;
}

static int mx_exec_err_out(char *command, char *arguments, int err) {
    char *buf = mx_strjoin("env: ", command);
    errno = err;
    DIR *dp;

    if (err == 2 && mx_get_char_index(arguments, '/') < 0)
        return err_helper(buf, 1, errno);
    if (err == 2)
        return err_helper(buf, 2, errno);
    if (err == 13 && (dp = opendir(command))) {
        closedir(dp);
        return err_helper(buf, 3, errno);
    }
    perror(buf);
    free(buf);
    return 126;
}

static int mx_find_status(int status, char *command, char *arguments) {
    switch WEXITSTATUS(status) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return mx_exec_err_out(command, arguments, WEXITSTATUS(status));
    }
}

static char *create_str_for_exec(char *command, char *arguments) {
    char *s = 0;
    mx_str_append(&s, command);
    mx_str_append(&s, " ");
    mx_str_append(&s, arguments);
    return s;
}

static void sighandler(int num) {
    num++;
}

static void sighandler_c(int num) {
    num++;
}

static char **prepare_array(char *command, char *arguments) {
    char *temp = mx_path_resolve_all_escapes(arguments);
    char *s = create_str_for_exec(command, temp);
    mx_strdel(&temp);

    char **result = mx_split_array_of_a_command(s);
    mx_strdel(&s);
    return result;
}

int mx_env_exec(char *command, char *arguments, char *path) {
    pid_t pid;
    pid_t wpid;
    int status;
    int exit_status;
    char **arr = prepare_array(command, arguments);
    char *external_path = mx_find_external_storage_path(command, path);

    pid = fork();
    if (pid == 0) {
        if (external_path != NULL) {
            if ((execv(external_path, arr)) < 0) {
                exit(errno);
            }
            exit(EXIT_SUCCESS);
        }
        if ((execv(arr[0], arr)) < 0) {
            exit(errno);
        }
        exit(EXIT_SUCCESS);
    }
    signal(SIGINT, sighandler_c);
    signal(SIGTSTP, sighandler); 

    wpid = waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpid());
    exit_status = mx_find_status(status, command, arguments);
    mx_del_strarr(&arr);

    return exit_status;
}
