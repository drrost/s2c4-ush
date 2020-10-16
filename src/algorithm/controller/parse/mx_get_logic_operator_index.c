#include <ush.h>

int mx_get_logic_operator_index(const char *str, char operator) {
    if (mx_strlen(str)) {
        for (int j = 0; str[j] != '\0'; j++) {
            if (str[j] == operator && str[j + 1] == operator
                && j > 0 && str[j - 1] != '\\')
                return j;
        }
    }
    return -1;
}
