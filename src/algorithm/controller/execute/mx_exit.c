//
// Created by Karina Barinova on 28.09.2020.
//

#include <ush.h>

//static int question(t_env *env) {
//    t_env *head = env;
//
//    while (head) {
//        if (head->name[0] == '?' && head->name[1] == '\0')
//            return atoi(head->value);
//        head = head->next;
//    }
//    return 0;
//}
//
//static void exit_err(char *line, int flag) {
//    switch (flag) {
//        case 1:
//            if (isatty(0))
//                mx_printstr("exit\n");
//            mx_printerr("ush: ");
//            if (!isatty(0))
//                mx_printerr("line 1: ");
//            mx_printerr("exit: too many arguments\n");
//            break;
//        default:
//            if (isatty(0))
//                mx_printstr("exit\n");
//            mx_printerr("ush: ");
//            if (!isatty(0))
//                mx_printerr("line 1: ");
//            mx_printerr("exit: ");
//            mx_printerr(line);
//            mx_printerr(": numeric arguments required\n");
//            break;
//    }
//}

//static int
//exit_status(char *line, int count, bool *error, t_env *environment) {
//    if (count == 1)
//        return question(environment);
//    if (count != 1) {
//        for (int i = 0; line[i]; i++) {
//            if (line[0] == '+' || line[0] == '-')
//                continue;
//            if (!isdigit(line[i])) {
//                *error = true;
//                return -1;
//            }
//        }
//        if (count == 2)
//            return atoi(line);
//    }
//    *error = true;
//    return 1;
//}

int mx_exit(char *line) {
    if (mx_strlen(line) > 0)
        mx_setenv("EXIT_CODE", line);

    return MX_SHOULD_EXIT;

//    bool error = false;
//    int count = 0;
//
//    while (line[count])
//        count++;
//    int i = exit_status(line, count, &error, environment);
//
//    if (count != 1 && error && i != -1) {
//        mx_env_replace(&environment, "?=1");
//        exit_err(line, 1);
//        return 0;
//    }
//    if (i == -1 && error) {
//        exit_err(line, 2);
//        return -1;
//    }
//    if (isatty(0))
//        mx_printstr("exit\n");
//
//    return i;
}
