//
// Created by Rostyslav Druzhchenko on 24.09.2020.
//

#include <ush.h>

static int exit_code() {
    char *code_s = mx_getenv("GLOBAL_EXIT_CODE");
    return code_s ? atoi(code_s) : 0;
}

int main(int argc, const char *argv[]) {
    mx_check_input(argc, argv);

    mx_core_init();

    mx_run_algorithm();
    int code = exit_code();
    mx_core_clean();

    return code;
}
