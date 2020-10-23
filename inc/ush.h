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
#define MX_SPACE_SUBSTITUTION "YLTHktK7wcrFOnYm5hA2jJp1A9p71j"
#define MX_APPOS_SUBSTITUTION "V2yJOHF1Qq20unsWnmN4TVamOLni4j"
#define MX_SLASH_SUBSTITUTION "xpDVKjP1s7gJzVLY9KV6XgVJrrddOzf"

int mx_execute(t_input *input);
int mx_run_built_in(char *command, char *arguments);
int mx_run_exec(char *command, char *arguments);

t_input *mx_parse_input(const char *input);
t_input *mx_parse_input_simple(const char *str);

// BUILT_IN
int mx_pwd(char *line);
int mx_echo(char *args, int exit_code);
int mx_exit(char *line);
int mx_env(char *args);
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
int mx_fg(char *args);
int mx_about(void);

void mx_env_replace(t_env **env, char *data);
t_env *fill_env(char *env[]);

// UTILS
void mx_printerr(const char *str);
bool mx_is_built_in(char *str);
int mx_command_not_found(const char *s);
char *mx_clear_str_of_symbols(const char *line);
int mx_unsetenv(const char *s);
int mx_print_not_found(const char *s);
int mx_env_i(char **arr, int i);
int mx_env_u(char **arr, int i);
int mx_print_option_required(char c);
void mx_print_env(void);
void mx_printerr_char(char c);
char **mx_split_array_of_a_command(char *line);
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
int mx_env_exe(char **arr, int binary_index, char *path);
int mx_env_flag_u(char **arr);
int mx_env_flag_i(char **arr);
void error_msg(char *option);
int print_env_without_var(char *var_name);
void mx_option_requires_an_argument(char *option);
char **correct_command_retriever(char **old_arr, int bin_index);
char *mx_substr_retriever(char *src_str, int indx1, int indx2);
char **mx_new_strarr(int number_of_str);
char *mx_string_copy(char *str);
char **mx_arr_copy(char **old_arr);
void mx_print_env(void);
void mx_specified_vars_setter(char **arr, int start);
int mx_binary_index_finder(char **arr, int start);
int mx_is_in_arr(char *s, char c);
int mx_env_flag_p(char **arr);
int mx_env_exec(char *command, char *arguments, char *path);
char *mx_three_join(char *str1, char *str2, char *str3);
void mx_check_input(int argc, const char *argv[]);

#endif
