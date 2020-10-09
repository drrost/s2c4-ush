//
// Created by Karina Barinova on 08.10.2020.
//

#include <ush.h>

int mx_unset(char *arguments) {
	if (mx_strlen(arguments)) {

	}
	else {
		mx_printerr("unset: not enough arguments\n");
		return 1;
	}
	return 0;
}
