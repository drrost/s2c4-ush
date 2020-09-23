#include "libmx.h"

static int compare(char *s1, char *s2);

int mx_bubble_sort(char **arr, int size) 
{
    int count = 0;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (compare(arr[j], arr[j +1]) > 0) {
                count++;
                // swap j and j+1
                char *t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
    return count;
}

static int compare(char *s1, char *s2) 
{
    return mx_strcmp(s1, s2);
}
