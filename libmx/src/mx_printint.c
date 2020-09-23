#include "libmx.h"

void mx_printint(int n) {
    char s[10];
    int i = 0;

    if (n == 0)
        mx_printchar('0');
    if (n < 0)
        mx_printchar('-');
    while (n != 0) {
        if (n > 0)
            s[i] = n % 10 + '0';
        else
            s[i] = n % 10 * (-1) + '0';
        i++;
        n /= 10;
    }
    i -= 1;
    while (i >= 0) {
        mx_printchar(s[i]);
        i--;
    }
}
