//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <ush.h>

const char *mx_get_home_dir() {
    return mx_getenv("HOME");
}
