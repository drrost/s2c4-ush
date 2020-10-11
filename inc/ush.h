#ifndef USH_H
#define USH_H

#include <libmx.h>
#include <algorithm.h>
#include <mx_core.h>

// System headers

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <pwd.h>


void check_leaks();

// Algorithm

void mx_run_algorithm();
char *mx_read_next();

#define MX_SHOULD_EXIT -3
#define MX_SHOULD_NEXT 0
int mx_execute(t_input *input);

t_input *mx_parse_input(const char *input);
t_input *mx_parse_input_simple(const char *str);

// BUILT_IN
int mx_pwd(char *line);
int mx_echo(char *args, int exit_code);
int mx_exit(char *line);
int mx_env(const char *args);
int mx_false(void);
int mx_true(void);
int mx_which(char *arguments);
int mx_change_color(char *command);
int mx_unset(char *arguments);
int mx_export(char *arguments);
int mx_bye(char *line);
int mx_whoami(char *line);
int mx_cd(const char *line);

void mx_env_replace(t_env **env, char *data);
t_env *fill_env(char *env[]);

// UTILS
void mx_printerr(const char *str);
bool mx_is_built_in(char *str);
int command_not_found(const char *s);
int echo_flag(char *str, int *n);
char *clear_str_of_symbols(const char *line);
int mx_unsetenv(const char *s);
int mx_arr_size(char **arr);
int env_not_found(const char *s);
int env_i(char **arr, int i);
int env_u(char **arr, int i);
int env_option_required(char c);
void print_env(void);

enum e_log_level {
    LOG_ALL,
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
    LOG_OFF
};

void mx_log(const char *subject, const char *details, int level);
void mx_log_t(const char *subject, const char *details);
void mx_log_d(const char *subject, const char *details);
void mx_log_i(const char *subject, const char *details);
void mx_log_e(const char *subject, const char *details);

#endif
