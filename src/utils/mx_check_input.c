//
// Created by Karina Barinova on 22.10.2020.
//

#include <ush.h>

void mx_check_input(int argc, const char *argv[]) {
    if (argc > 1) {
        mx_printerr("ush: can't open input file: ");
        mx_printerr(argv[1]);
        mx_printerr("\n");
        exit(127);
    }
}
