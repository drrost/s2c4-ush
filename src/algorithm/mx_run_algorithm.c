//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

void mx_run_algorithm() {
    while (true) {
        // read next line
        char *line = mx_read_next();

        // parse the line
        t_input *input = mx_parse_input(line);

        // execute
        mx_execute(input);
    }
}
