//
// Created by Rostyslav Druzhchenko on 24.09.2020.
//

#include <ush.h>

int main(int argc, const char *argv[]) {
    mx_print_debug("run app", "");

    mx_run_algorithm();
    check_leaks();

    argc++;
    argv++;
    return 0;
}
