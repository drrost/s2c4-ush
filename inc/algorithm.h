//
// Created by Rostyslav Druzhchenko on 30.09.2020.
//

#ifndef INC_04_USH_ALGORITHM_H
#define INC_04_USH_ALGORITHM_H

#include <stdbool.h>
#include <stdlib.h>
#include <libmx.h>

#define MX_DELIM_NO_PAIR "ush: symbol not found: \" \n"
#define MX_DELIM_NO_PAIR2 "ush: symbol not found: ` \n"
#define MX_DELIM_NO_PAIR3 "ush: symbol not found: ( \n"
#define MX_DELIM_NO_PAIR4 "ush: symbol not found: ) \n"
#define MX_DELIM_NO_PAIR5 "ush: Odd number of quotes. \n"

typedef struct {
    char *name;
    char *arguments;
    int exit_code;
    char *output;
    char *error_text;
    bool has_and;
    bool has_or;
    bool is_last_in_sequesce;
    bool pass_out_to_next;
    bool get_input_from_prev;
} t_command;

// Input
//
typedef struct {
    char *error_text;
    t_list *commands;
} t_input;

t_command *mx_command_new();
void create_comm_and_arg(t_input *input, int end, char *strend, int start, bool has_and);
char *mx_error_pair(const char *str);
bool get_subst(const char *str);
char *mx_get_command(char *str);
char *mx_get_args(char *str);
char *mx_substr(const char *src, int start, int end);
int mx_get_logic_operator_index(const char *str, char operator);

// Env
//
typedef struct s_env {
    char *name;
    char *value;
    struct s_env *next;
}              t_env;

t_input *mx_input_new();
void mx_input_delete(t_input **instance);
void mx_command_delete(t_command **command);

// Terminal state
//

typedef struct {
    int pos;
    int size;
    t_list *list;
} t_history_state;

typedef struct {
    int cursor_pos;
    char *line;
    char *backup_line;
    t_history_state history_state;
} t_termstate;

t_termstate *mx_termstate_new(t_list *history);
void mx_termstate_del(t_termstate **state);
void mx_termstate_history_up(t_termstate *this);
void mx_termstate_history_down(t_termstate *this);

#endif //INC_04_USH_ALGORITHM_H
