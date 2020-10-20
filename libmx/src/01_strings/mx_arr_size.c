//
// Created by Karina Barinova on 09.10.2020.
//

#include <ush.h>

int mx_arr_size(char **arr) {
    int i = 0;

    if (arr != NULL) {
        while (arr[i])
            i++;
        return i;
    }
    return 0;
}
