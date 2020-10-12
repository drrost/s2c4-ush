//
// Created by Rostyslav Druzhchenko on 12.10.2020.
//

#include <ush.h>

bool mx_is_arrow_up(const char *s) {
    return s[0] == 27 && s[1] == 91 && s[2] == 65;
}

bool mx_is_arrow_down(const char *s) {
    return s[0] == 27 && s[1] == 91 && s[2] == 66;
}

bool mx_is_arrow_right(const char *s) {
    return s[0] == 27 && s[1] == 91 && s[2] == 67;
}

bool mx_is_arrow_left(const char *s) {
    return s[0] == 27 && s[1] == 91 && s[2] == 68;
}
