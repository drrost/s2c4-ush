//
// Created by Karina Barinova on 28.09.2020.
//

#include <ush.h>
//#include <stdlib.h>
#include <unistd.h>

//static int question() //to set up environment status

static void exit_err(char *line, int flag) {
	switch(flag) {
		case 1:
			if (isatty(0))
				mx_printstr("exit\n");
			mx_printerr("ush: ");
			if (!isatty(0))
				mx_printerr("line 1: ");
			mx_printerr("exit: too many arguments\n");
			break;
		default:
			if (isatty(0))
				mx_printstr("exit\n");
			mx_printerr("ush: ");
			if (!isatty(0))
				mx_printerr("line 1: ");
			mx_printerr("exit: ");
			mx_printerr(line);
			mx_printerr(": numeric arguments required\n");
			break;
	}
}

static int exit_status(char *line, int count, bool *error) {
	//if (count == 1)
	//	return question();
	if (count != 1) {
		for (int i = 0; line[i]; i++) {
			if (line[0] == '+' || line[0] == '-')
				continue;
			if (!isdigit(line[i])) {
				*error = true;
				return -1;
			}
		}
		if (count == 2)
			return atoi(line);
	}
		*error = true;
		return 1;
}

void mx_exit(char *line) {
	bool error = false;
	int count = 0;

	while (line[count])
		count++;
	int i = exit_status(line, count, &error);

	if (count != 1 && error && i != -1) {
		exit_err(line, 1);
		return;
	}
	if (i == -1 && error) {
		exit_err(line, 2);
		exit(-1);
	}
	if (isatty(0))
		mx_printstr("exit\n");
	exit(i);
}
