//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

//static void print_input(t_input *main) {
//
//    while(main->commands){
//        mx_printstr("data->subs: ");
//        mx_printint((int )((t_command *)main->commands->data)->get_input_from_prev);
//        mx_printstr("\n");
//        mx_printstr("data->name: ");
//        mx_printstr(((t_command *)main->commands->data)->name);
//        mx_printstr("\n");
//        mx_printstr("data->arguments: ");
//        if (((t_command *)main->commands->data)->arguments != NULL)
//            mx_printstr(((t_command *)main->commands->data)->arguments);
//        else
//            mx_printstr("NULL");
//        mx_printstr("\n");
//        mx_printstr("data->stop_on_fail: ");
//        mx_printint((int )((t_command *)main->commands->data)->stop_on_fail);
//        mx_printstr("\n");
//        mx_printstr("===============================================\n");
//        main->commands = main->commands->next;
//    }
//}

static void print_prompt() {
    printf("u$l> ");
}

void mx_run_algorithm(char *env[]) {
//    t_env *environment = fill_env(env);
    env++;

    while (true) {
        // Read
        print_prompt();
        char *line = mx_read_next();

        // Parse

        t_input *input = mx_parse_input(line);
        mx_error_pair(line);
//        mx_strdel(&line);
//        print_input(input);
        break;

        // Execute
        int result = mx_execute(input);

        // Next
        mx_input_delete(&input);
        if (result == MX_SHOULD_EXIT)
            break;
    }
}
