//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

static void print_prompt() {
    printf("u$l> ");
}

void mx_run_algorithm() {
    while (true) {
        // Read
        print_prompt();
        char *line = mx_read_next();

        // Parse
        t_input *input = mx_parse_input(line);
        mx_strdel(&line);

        // Execute
        int result = mx_execute(input);

        // Next
        mx_input_delete(&input);
        if (result == MX_SHOULD_EXIT)
            break;
    }
}
