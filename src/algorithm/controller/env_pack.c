//
// Created by Karina Barinova on 28.09.2020.
//

#include <ush.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

void mx_env_add(t_env **env, char *data) {
    t_env *buf = NULL;
    t_env *head = *env;

    if (!data)
        return;
    buf = malloc(sizeof(t_env));
    buf->name = strndup(data, mx_get_char_index(data, '='));
    buf->value = strndup(data + mx_get_char_index(data, '=') + 1, strlen(data)
        - mx_get_char_index(data, '='));
    buf->next = NULL;

    if (!*env) {
        *env = buf;
        return;
    }
    while (head->next) {
        head = head->next;
    }
    head->next = buf;
}

void mx_env_replace(t_env **env, char *data) {
    t_env *head = *env;
    char *buf_name = strndup(data, mx_get_char_index(data, '='));
    while (head) {
        if (strcmp(head->name, buf_name)) {
            //mx_strdel(&head->value);
            head->value = strndup(data + mx_get_char_index(data, '=') + 1, strlen(data)
                - mx_get_char_index(data, '='));
            //mx_strdel(&buf_name);
            return;
        }
        head = head->next;
    }
    mx_strdel(&buf_name);
    mx_env_add(env, data);
}

static t_env *env_get_path(t_env *env) {
    char buf[] =
    "PLA/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:PLA";
    char *home = mx_strjoin(getenv("HOME"), "/.brew/bin");
    char *buf2 = mx_replace_substr(buf, "PLA", home);
    char *buf3 = mx_strjoin("PATH=", buf2);

    setenv("PATH", buf2, 1);
    mx_env_replace(&env, buf3);
    mx_strdel(&home);
    mx_strdel(&buf2);
    mx_strdel(&buf3);
    return env;
}

static t_env *env_gethome_level(int flag, t_env *env) {
    if (flag == 1) {
        struct passwd *pass = getpwuid(getuid());
        char *home = mx_strjoin("HOME=", strdup(pass->pw_dir));
        mx_env_add(&env, home);
        setenv("HOME", pass->pw_dir, 1);
        mx_strdel(&home);
    }
    if (flag == 2) {
        setenv("SHLVL", "1", 1);
        mx_env_add(&env, "SHLVL=1");
    }
    if (flag == 3) {
        setenv("_", "env", 1);
        mx_env_add(&env, "_=env");
    }
    if (flag == 4) {
        struct passwd *pass = getpwuid(getuid());
        setenv("LOGNAME", pass->pw_name, 1);
    }
    return env;
}

static t_env *env_get_pwd(int flag, t_env *env) {
    char *buf = mx_strnew(1024);
    char *buf2 = NULL;
    char *buf3 = NULL;

    if (flag == 1) {
        getcwd(buf, 1024);
        buf2 = mx_strjoin("PWD=", buf);
        buf3 = mx_strjoin("OLDPWD=", buf);
        setenv("PWD", buf, 1);
        setenv("OLDPWD", buf, 1);
        mx_env_add(&env, buf2);
        mx_env_add(&env, buf3);
        mx_strdel(&buf3);
    }
    mx_strdel(&buf);
    mx_strdel(&buf2);
    return env;
}

void env_shlvl(t_env *env) {
    int cur = atoi(getenv("SHLVL")) + 1;
    char *buf = mx_itoa(cur);
    char *buf2 = mx_strjoin("SHLVL=", buf);

    setenv("SHLVL", buf, 1);
    mx_env_replace(&env, buf2);
    mx_strdel(&buf);
    mx_strdel(&buf2);
}

t_env *fill_env_el(void) {
    t_env *environment = NULL;

    environment = env_get_pwd(1, environment);
    if (!(getenv("HOME")))
        environment = env_gethome_level(1, environment);
    if (!(getenv("SHLVL")))
        environment = env_gethome_level(2, environment);
    else
        env_shlvl(environment);
    if (!(getenv("_")))
        environment = env_gethome_level(3, environment);
    if (!(getenv("PATH")))
        environment = env_get_path(environment);
    if (!getenv("LOGNAME"))
        environment = env_gethome_level(4, environment);
    return environment;
}

t_env *fill_env(char *env[]) {
    t_env *environment = fill_env_el();
    
    for ( int i = 0; env[i]; i++) {
        mx_env_add(&environment, env[i]);
    }
    mx_env_add(&environment, "?=0");
    return environment;
}
