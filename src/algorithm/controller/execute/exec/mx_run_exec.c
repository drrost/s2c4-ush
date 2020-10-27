//
// Created by Karina Barinova on 13.10.2020.
//

#include <ush.h>
#include <mx_log.h>

static int err_helper(char *buf, int status, int err, char *command) {
    errno = err;

    switch (status) {
        case 1:
            mx_printerr(buf);
            mx_printerr("command not found: ");
            mx_printerr(command);
            mx_printerr("\n");
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
    char *buf = mx_strdup("ush: ");
    errno = err;
    DIR *dp;

    if (err == 2 && mx_get_char_index(arguments, '/') < 0)
        return err_helper(buf, 1, errno, command);
    if (err == 2)
        return err_helper(buf, 2, errno, command);
    if (err == 13 && (dp = opendir(command))) {
        closedir(dp);
        return err_helper(buf, 3, errno, command);
    }
    if (err == 18) {
        free(buf);
        return 146;
    }
    mx_printerr("ush: ");
    perror(command);
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
    mx_printline("");
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

int mx_run_exec(char *command, char *arguments) {
    pid_t pid;
    pid_t wpid;
    int status;
    int exit_status;
    char **arr = prepare_array(command, arguments);

    pid = fork();

    if (pid == 0) { // Child process
        // signup for shortcuts

        if (!mx_getenv("PATH")) {
            if ((execv(command, arr)) < 0) {
                exit(errno);
            }
            exit(EXIT_SUCCESS);
        }
        if ((execvp(command, arr)) < 0) {
            exit(errno);
        }
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
    exit_status = mx_find_status(status, command, arguments);

    mx_del_strarr(&arr);

    return exit_status;
}
