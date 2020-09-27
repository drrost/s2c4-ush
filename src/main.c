//
// Created by Rostyslav Druzhchenko on 24.09.2020.
//

#include <ush.h>

int main(int argc, const char *argv[]) {
    mx_log_t("Entering ULS", "");

    mx_run_algorithm();
    check_leaks();

    argc++;
    argv++;

    mx_log_t("Exitign ULS", "");

    return 0;
}
