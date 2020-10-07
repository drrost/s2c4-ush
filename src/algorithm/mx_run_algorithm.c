//
// Created by Rostyslav Druzhchenko on 26.09.2020.
//

#include <ush.h>

static void print_prompt() {
    t_map *map = mx_map_str_str();
    map->set(map, "pwd", "/usr/local/bin");
    map->set(map, "TMPDIR",
             "/var/folders/1q/6yl13mjx38g2jgfhx6072t180000gn/T/");
    char *pwd = map->get(map, "pwd");
    pwd++;

    mx_map_print(map);
    mx_map_delete(&map);

    printf("u$l> ");
}

void mx_run_algorithm() {
    while (true) {
        // Read
        print_prompt();
        char *line = mx_read_next();

        // Parse
        t_input *input = mx_parse_input_simple(line);
        mx_strdel(&line);

        // Execute
        int result = mx_execute(input);

        // Next
        mx_input_delete(&input);
        if (result == MX_SHOULD_EXIT)
            break;
    }
}
