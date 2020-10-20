//
// Created by Karina Barinova on 13.10.2020.
//

#include <ush.h>
#include <private/mx_run_exec_private.h>
#include <mx_log.h>

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

void sighandler(int num) {
    num++;
}

void sighandler_c(int num) {
    num++;
}

int mx_run_exec(char *command, char *arguments) {
    pid_t pid;
    pid_t wpid;
    int status;
    char *s = create_str_for_exec(command, arguments);
    char *old = s;
    s = mx_replace_spaces_to_magic(s);
    mx_strdel(&old);

    char **arr = mx_strsplit(s, ' ');
    mx_handle_spaces(arr);

    pid = fork();

    mx_log_di("!! pid", pid);

    if (pid == 0) { // Child process
        // signup for shortcuts

        if (!mx_getenv("PATH")) {
            if ((execv(command, arr)) < 0) {
                mx_log_d("exiting a process", 0);
                exit(errno);
            }
            mx_log_d("exiting a process", 0);
            exit(EXIT_SUCCESS);
        }
        if ((execvp(command, arr)) < 0) {
            mx_log_d("exiting a process", 0);
            exit(errno);
        }
        mx_log_d("exiting a process", 0);
        exit(EXIT_SUCCESS);
    }

    // Continue the main process
    // signup for shortcuts
    // TODO: Move to core init
    //
    signal(SIGINT, sighandler_c); // CTRL+C
    signal(SIGTSTP, sighandler); // CTRL+Z

    wpid = waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpid());
    mx_find_status(status, command, arguments);

    mx_del_strarr(&arr);
    mx_strdel(&s);

    return 0;
}
