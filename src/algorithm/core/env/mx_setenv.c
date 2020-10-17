//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_core.h>

void mx_setenv(const char *key, const char *value) {
    setenv(key, value, true);
}
