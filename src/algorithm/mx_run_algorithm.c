//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

void mx_run_algorithm() {
    bool is_tty = isatty(fileno(stdin));

    while (true) {
        // Read
        char *line = mx_read_next();

        // Parse
        t_input *input = mx_parse_input(line);
        mx_strdel(&line);

        // Execute
        int result = MX_SHOULD_NEXT;
        if (input->error_text)
            mx_printerr(input->error_text);
        else
            result = mx_execute(input);

        mx_input_delete(&input);

        // Next
        if (result == MX_SHOULD_EXIT || is_tty == false)
            break;
    }
}
