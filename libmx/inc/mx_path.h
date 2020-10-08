//
// Created by Rostyslav Druzhchenko on 08.10.2020.
//

#ifndef INC_04_USH_MX_PATH_H
#define INC_04_USH_MX_PATH_H

typedef struct s_path {
    char *p;

    char *(*last)(struct s_path *, char *);
    void (*last_del)(struct s_path *);
    void (*append)(struct s_path *, char *);
    void (*print)(struct s_path *);
}              t_path;

t_path *mx_path_new(const char *path);
void mx_pant_del(t_path **path);

#endif //INC_04_USH_MX_PATH_H
