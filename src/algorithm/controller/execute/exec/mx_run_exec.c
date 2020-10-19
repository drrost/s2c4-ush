//
// Created by Karina Barinova on 13.10.2020.
//

#include <ush.h>

static int err_helper(char *buf, int status, int err) {
    errno = err;

    switch (status) {
        case 1:
            mx_printerr(buf);
            mx_printerr(": command not found\n");
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
    char *buf = mx_strjoin("ush: ", command);
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

char *create_str_for_exec(char *command, char *arguments) {
    char *s = 0;
    mx_str_append(&s, command);
    mx_str_append(&s, " ");
    mx_str_append(&s, arguments);
    return s;
}

static char *replace_spaces_to_magic(char *line) {
    return mx_str_replace(line, "\\ ", MX_SPACE_SUBSTITUTION);
}

static char *replace_magic_to_spaces(char *line) {
    return mx_str_replace(line, MX_SPACE_SUBSTITUTION, " ");
}

static void handle_spaces(char **arr) {
    int i = 0;

    while (arr[i]) {
        char *old = arr[i];
        arr[i] = replace_magic_to_spaces(arr[i]);
        mx_strdel(&old);
        i++;
    }
}

int mx_run_exec(char *command, char *arguments) {
    pid_t pid;
    pid_t wpid;
    int status;
    char *s = create_str_for_exec(command, arguments);
    char *old = s;
    s = replace_spaces_to_magic(s);
    mx_strdel(&old);

    char **arr = mx_strsplit(s, ' ');
    handle_spaces(arr);

    pid = fork();
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        if (!mx_getenv("PATH")) {
            if ((execv(command, arr)) < 0)
                exit(errno);
            exit(EXIT_SUCCESS);
        }
        if ((execvp(command, arr)) < 0)
            exit(errno);
        exit(EXIT_SUCCESS);
    }
    wpid = waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpid());
    mx_find_status(status, command, arguments);
    mx_del_strarr(&arr);
    mx_strdel(&s);
    return 0;
}
