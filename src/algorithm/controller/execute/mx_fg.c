//
// Created by Karina Barinova on 16.10.2020.
//

#include <ush.h>

int mx_fg(char *args) {
	if (mx_strlen(args) > 0) {
		char **arr = mx_strsplit(args, ' ');
		
		mx_printerr("fg: job not found: ");
		mx_printerr(arr[0]);
		mx_printerr("\n");
		mx_del_strarr(&arr);
	}
	else
		mx_printerr("fg: no current job\n");
	return 1;
}
