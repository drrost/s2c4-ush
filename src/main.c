//
// Created by Rostyslav Druzhchenko on 24.09.2020.
//

#include <ush.h>
#include <mx_log.h>

static int exit_code() {
    char *code_s = mx_getenv("EXIT_CODE");
    return code_s ? atoi(code_s) : 0;
}

int main(int argc, const char *argv[]) {
    mx_log_t("Entering ULS", "");

    mx_core_init();

    mx_run_algorithm();
    int code = exit_code();
    mx_core_clean();

    check_leaks();

    argc++;
    argv++;

    mx_log_t("Exiting ULS", "");

    return code;
}
