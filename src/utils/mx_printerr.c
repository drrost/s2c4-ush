//
// Created by Karina Barinova on 25.09.2020.
//

#include <ush.h>
#include <unistd.h>

void mx_printerr(const char *str) {
	write(2, str, mx_strlen(str));
}
