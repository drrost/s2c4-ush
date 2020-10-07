#ifndef USH_H
#define USH_H

#include <libmx.h>
#include <algorithm.h>

// System headers

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

// File types

#define MX_IFMT 0170000 // Mask of file type
#define MX_IFIFO 0010000 // Named pipe(fifo)
#define MX_IFCHR 0020000 //character device
#define MX_IFDIR 0040000 //directory file
#define MX_IFBLK 0060000 //Block device
#define MX_IFREG 0100000 //regular file
#define MX_IFLNK 0120000 //symbolic link
#define MX_IFSOCK 0140000 //UNIX domain socket

#define MX_ISBLK(m) (((m) & MX_IFMT) == MX_IFBLK)
#define MX_ISCHR(m) (((m) & MX_IFMT) == MX_IFCHR)
#define MX_ISDIR(m) (((m) & MX_IFMT) == MX_IFDIR)
#define MX_ISFIFO(m) (((m) & MX_IFMT) == MX_IFIFO)
#define MX_ISREG(m) (((m) & MX_IFMT) == MX_IFREG)
#define MX_ISLNK(m) (((m) & MX_IFMT) == MX_IFLNK)
#define MX_ISXEC(m) ((m) & MX_IXUSR)
#define MX_ISSOCK(m) (((m) & MX_IFMT) == MX_IFSOCK)

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
void mx_env(const char *args);
int mx_false(void);
int mx_true(void);
int mx_which(char *arguments);

void mx_env_replace(t_env **env, char *data);
t_env *fill_env(char *env[]);

// UTILS
void mx_printerr(const char *str);
char *mx_getenv(const char *s);

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
