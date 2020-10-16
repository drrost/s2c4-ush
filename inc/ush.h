#ifndef USH_H
#define USH_H

#include <libmx.h>
#include <algorithm.h>
#include <mx_core.h>
#include <mx_ush_utils.h>

// System headers

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/ioctl.h>
#include <regex.h>
#include <errno.h>


void check_leaks();

// Algorithm

void mx_run_algorithm();
char *mx_read_next();

#define MX_SHOULD_EXIT -3
#define MX_SHOULD_NEXT 0
int mx_execute(t_input *input);
int mx_run_exec(char *command, char *arguments);

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
int mx_arch(char *args);

void mx_env_replace(t_env **env, char *data);
t_env *fill_env(char *env[]);

// UTILS
void mx_printerr(const char *str);
bool mx_is_built_in(char *str);
int mx_command_not_found(const char *s);
char *mx_clear_str_of_symbols(const char *line);
int mx_unsetenv(const char *s);
int mx_arr_size(char **arr);
int mx_print_not_found(const char *s);
int mx_env_i(char **arr, int i);
int mx_env_u(char **arr, int i);
int mx_print_option_required(char c);
void mx_print_env(void);
void mx_printerr_char(char c);
int mx_get_window_width();
bool mx_regex(char *str, char *regular);
int mx_get_hex_and_oct(char *buf, char *str, int *i);
bool mx_print_exit_code(int exit_code, char *s);
int mx_hex(char *str, int *i);
char *mx_checkflags_echo(char **arr, int *counter);
int mx_print_echo_d(char *str, int *i);
int mx_tolower(int c);
int mx_file_exist(char *path);
void mx_check_command(char *str, int *ret_flag, int flag);
int mx_is_builtin(char *command);
char *mx_command_in_path(char *comm, char *str_path);

#endif
