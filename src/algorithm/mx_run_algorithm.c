//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>
// static void print_input(t_input *main) {
//
//     while(main->commands){
//           mx_printstr("\n");
//         mx_printstr("data->name: ");
//         mx_printstr(((t_command *)main->commands->data)->name);
//         mx_printstr("name");
//         mx_printstr("\n");
//         mx_printstr("data->arguments: ");
//         if (((t_command *)main->commands->data)->arguments != NULL)
//             mx_printstr(((t_command *)main->commands->data)->arguments);
//         else
//             mx_printstr("NULL");
//         mx_printstr("\n");
//         mx_printstr("has or: ");
//         mx_printint((int )((t_command *)main->commands->data)->has_or);
//         mx_printstr("\n");
//         mx_printstr("has and: ");
//         mx_printint((int )((t_command *)main->commands->data)->has_and);
//         mx_printstr("\n");
//         mx_printstr("===============================================\n");
//         main->commands = main->commands->next;
//     }
// }

void mx_run_algorithm() {
    bool is_tty = isatty(fileno(stdin));

    while (true) {
        // Read
        char *line = mx_read_next();

        // Parse
        t_input *input = mx_parse_input(line);
//        print_input(input);
//        break;
        mx_strdel(&line);

        // Execute
        int result = mx_execute(input);
        mx_input_delete(&input);

        // Next
        if (result == MX_SHOULD_EXIT || is_tty == false)
            break;
    }
}
