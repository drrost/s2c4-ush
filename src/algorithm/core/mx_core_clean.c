//
// Created by Rostyslav Druzhchenko on 07.10.2020.
//

#include <mx_core.h>

void mx_core_clean() {
    mx_env_delete();
    mx_history_delete();
}
