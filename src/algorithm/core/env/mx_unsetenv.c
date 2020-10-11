//
// Created by Karina Barinova on 09.10.2020.
//

#include <ush.h>

int mx_unsetenv(const char *s) {
    t_map *env = mx_env_get();
    env->remove(env, (char *)s);
    // TODO: Possible handle error code
	return 0;
}
