//
// Created by Rostyslav Druzhchenko on 02.10.2020.
//

#include <ush.h>

int mx_arch(char *args) {
	if (!mx_strlen(args)) {
		mx_printline("i386");
	}
	else {
		char **arr = mx_strsplit(args, ' ');
		mx_printerr("arch: Can't find ");
		mx_printerr(arr[0]);
		mx_printerr(" in PATH\n");
		mx_del_strarr(&arr);
		return 1;
	}
	return 0;
}
