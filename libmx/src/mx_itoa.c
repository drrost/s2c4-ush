#include "libmx.h"

static void nbrtodec_rec(int n, char *s);

static void add(int last_digit, char *s);

char *mx_itoa(int nbr) 
{
    if (nbr == -2147483648) {
        char *s = mx_strdup("-2147483648");
        return s;
    }
    char *s = mx_strnew(11);
    if (nbr < 0) {
        s[0] = '-';
        nbr = -nbr;
    }
    nbrtodec_rec(nbr, s);
    return s;
}

static void nbrtodec_rec(int n, char *s) 
{
    int last_digit = n % 10;
    if (n >= 10) {
        nbrtodec_rec(n / 10, s);
        add(last_digit, s);
    }
    else add(last_digit, s);
}

static void add(int last_digit, char *s) 
{
    while (*s) s++;
    *s = last_digit + '0';
}
