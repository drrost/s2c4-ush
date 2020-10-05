//
// Created by Rostyslav Druzhchenko on 30.09.2020.
//

#ifndef INC_04_USH_ALGORITHM_H
#define INC_04_USH_ALGORITHM_H

#include <stdbool.h>
#include <stdlib.h>
#include <libmx.h>

// Command
//
typedef struct {
    char *name;
    char *arguments;
    int exit_code;
    char *output;
    bool stop_on_fail;
} t_command;

t_command *mx_command_new();
void mx_command_delete(t_command **command);
char *substr(const char *src, int start, int end);
int get_logic_operator_index (const char *str, char operator);

// Input
//
typedef struct {
    char *command; // TODO: remove will not used
    t_list *commands;
} t_input;

// Env
//
// TODO: Rename to t_pair
//
typedef struct s_env {
    char *name;
    char *value;
    struct s_env *next;
}              t_env;

t_input *mx_input_new();
void mx_input_delete(t_input **instance);

// Terminal state
//
typedef struct {
    int pos;
    char *line;
} t_termstate;

t_termstate *mx_termstate_new();
void mx_termstate_del(t_termstate **state);

#endif //INC_04_USH_ALGORITHM_H
