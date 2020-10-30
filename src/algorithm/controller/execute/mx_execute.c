//
// Created by Rostyslav Druzhchenko on 27.09.2020.
//

#include <ush.h>

static void log_command_execution(t_command *command) {
    char *s = 0;

    mx_str_append(&s, "name: \"");
    mx_str_append(&s, command->name);
    mx_str_append(&s, "\"");
    if (mx_strlen(command->arguments)) {
        mx_str_append(&s, ", arguments: \"");
        mx_str_append(&s, command->arguments);
        mx_str_append(&s, "\"");
    }

    mx_strdel(&s);
}

int mx_run_built_in(char *command, char *arguments) {
    int exit_code = 0;

    if (mx_streq(command, "color"))
        exit_code = mx_change_color(arguments);
    else if (mx_streq(command, "export"))
        exit_code = mx_export(arguments);
    else if (mx_streq(command, "unset"))
        exit_code = mx_unset(arguments);
    else if (mx_streq(command, "exit"))
        return mx_exit(arguments);
    else if (mx_streq(command, "bye"))
        return mx_bye(command);
    else if (mx_streq(command, "cd"))
        exit_code = mx_cd(arguments);
    else if (mx_streq(command, "pwd"))
        exit_code = mx_pwd(arguments);
    else if (mx_streq(command, "whoami"))
        exit_code = mx_whoami(arguments);
    else if (mx_streq(command, "which"))
        exit_code = mx_which(arguments);
    else if (mx_streq(command, "echo"))
        exit_code = mx_echo(arguments);
    else if (mx_streq(command, "true"))
        exit_code = mx_true();
    else if (mx_streq(command, "false"))
        exit_code = mx_false();
    else if (mx_streq(command, "env"))
        exit_code = mx_env(arguments);
    else if (mx_streq(command, "env"))
        exit_code = mx_env(arguments);
    else if (mx_streq(command, "arch"))
        exit_code = mx_arch(arguments);
    else if (mx_streq(command, "fg"))
        exit_code = mx_fg(arguments);
    else if (mx_streq(command, "about"))
        exit_code = mx_about();

    return exit_code;
}

static void run_command(t_command *command) {
    if (command->subs_set.pass_out_to_next)
        mx_start_stdout_interception();

    int exit_code = 0;
    if (mx_is_built_in(command->name))
        exit_code = mx_run_built_in(command->name, command->arguments);
    else if (!mx_strlen(command->name))
        exit_code = 0;
    else
        exit_code = mx_run_exec(command->name, command->arguments);
    command->exit_code = exit_code;

    if (command->subs_set.pass_out_to_next)
        command->subs_set.output = mx_end_stdout_interception();
}

int mx_execute(t_input *input) {
    int exit_code = MX_SHOULD_NEXT;

    t_list *list = input->commands;
    while (list) {
        t_command *command = (t_command *)list->data;

        mx_resolve_all(command);
        log_command_execution(command);
        if (mx_strstr(command->arguments, "~") != NULL)
            mx_expand_tilda(command);

        run_command(command);
        exit_code = command->exit_code;

        if (command->subs_set.pass_out_to_next) {
            t_command *next = (t_command *)list->next->data;
            if (next != NULL) {
                mx_str_replace_p(
                    &(next->arguments), MX_RUN_SUBSTITUTION,
                    command->subs_set.output);
            }
        }

        mx_setenv_i("EXIT_CODE", exit_code);

        list = list->next;
    }

    return exit_code;
}
