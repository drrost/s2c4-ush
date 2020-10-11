//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#include <libmx.h>

char *mx_path_resolve(t_path *this, const char *home_dir, const char *pwd) {
    char *result = 0;

    if (this == 0 || this->p == 0)
        return 0;

    if (this->p[0] == '/')
        return mx_strdup(this->p);

    if (this->p[0] == '~') {
        result = mx_strdup(home_dir);
        mx_str_append(&result, this->p + 1);
        return result;
    }

    if (mx_streq(".", this->p))
        return mx_strdup(pwd);

    if (mx_streq("..", this->p)) {
        t_path *temp = mx_path_new(pwd);
        temp->last_del(temp);
        result = mx_strdup(temp->p);
        mx_path_del(&temp);
        return result;
    }

    t_path *path = mx_path_new(pwd);
    path->append(path, this->p);
    result = mx_strdup(path->p);
    mx_path_del(&path);

    return result;
}
