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
    char **arr = (char **)malloc((number_of_str + 1) * sizeof(char *));

    arr[number_of_str] = NULL;
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
    int len     = mx_arr_size(old_arr);
    char **copy = mx_new_strarr(len);
    int i;

    i = 0;
    while(old_arr[i]) {
        copy[i] = mx_string_copy(old_arr[i]);
        i++;
    }
    return copy;
}
