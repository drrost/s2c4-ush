//
// Created by Rostyslav Druzhchenko on 16.10.2020.
//

#ifndef INC_04_USH_MX_USH_UTILS_H
#define INC_04_USH_MX_USH_UTILS_H

void mx_start_stdout_interception();
char *mx_end_stdout_interception();

void mx_resolve_all(t_command *command);
char *mx_resolve_envvars(char *s);
char *mx_trim_quotes(char *line);

#endif //INC_04_USH_MX_USH_UTILS_H
