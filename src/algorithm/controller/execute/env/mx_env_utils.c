//
// Created by Karina Barinova on 22.10.2020.
//

#include <ush.h>

char *mx_substr_retriever(char *src_str, int indx1, int indx2) {
    if (indx1 > indx2 || src_str == NULL)
        return NULL;
    char *sub = mx_strnew((indx2 + 1) - indx1);
    int index = 0;

    while(indx1 <= indx2) {
        sub[index] = src_str[indx1];
        indx1++;
        index++;
    }
    return sub;
}

char **mx_new_strarr(int number_of_str) {
    int size = (number_of_str + 1) * sizeof(char *);
    char **arr = (char **)malloc(size);
    mx_memset(arr, 0, size);
    return arr;
}

char *mx_string_copy(char *str) {
    char *new_str = mx_strnew(mx_strlen(str));
    char *pointer = new_str;
    int i = 0;

    while(str[i]) {
        *pointer = str[i];
        pointer++;
        i++;
    }
    pointer = NULL;
    return new_str;
}

char **mx_arr_copy(char **old_arr) {
    int size = mx_arr_size(old_arr);
    char **new_arr = mx_new_strarr(size);

    for (int i = 0; i < size; i++)
        new_arr[i] = mx_strdup(old_arr[i]);

    return new_arr;
}
