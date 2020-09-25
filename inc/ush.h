#ifndef USH_H
#define USH_H

#include <libmx.h>

//File types

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

//BUILT_IN
void mx_pwd(char *line);

//UTILS
void mx_printerr(const char *str);

#endif
