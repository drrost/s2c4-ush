//
// Created by Karina Barinova on 09.10.2020.
//

#include <ush.h>

int mx_whoami(char *line) {
    if (!mx_strlen(line)) {
        struct passwd *pw;
        uid_t uid;

        uid = getuid();
        pw = getpwuid(uid);
        if (pw) {
            printf("%s\n", pw->pw_name);
            return 0;
        }
        mx_printerr("whoami: cannot find username for UID ");
        mx_printerr(mx_itoa((unsigned) uid));
        mx_printerr("\n");
        return 1;
    }
    else
        mx_printerr("usage: whoami\n");
    return 1;
}
