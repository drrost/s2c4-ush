//
// Created by Rostyslav Druzhchenko on 24.09.2020.
//

#include <ush.h>
#include <mx_log.h>

int main(int argc, const char *argv[]) {
    mx_log_t("Entering ULS", "");

    mx_core_init();

    mx_run_algorithm();
    mx_core_clean();

    check_leaks();

    argc++;
    argv++;

    mx_log_t("Exiting ULS", "");

    return 0;
}
