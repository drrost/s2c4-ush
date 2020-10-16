//
// Created by Rostyslav Druzhchenko on 16.10.2020.
//

#include <ush.h>
#include <private/mx_stdout_interception.h>

static int save_out_fd_access(int access) {
    static int save_out_fd = 0;
    if (access == MX_ACCESS)
        return save_out_fd;
    save_out_fd = access;
    return save_out_fd;
}

static int out_fd_access(int access) {
    static int out_fd = 0;
    if (access == MX_ACCESS)
        return out_fd;
    out_fd = access;
    return out_fd;
}

void mx_start_stdout_interception() {
    int out_fd = open(MX_STDOUT_STORE, O_RDWR | O_CREAT | O_TRUNC, 0600);
    out_fd_access(out_fd);

    int save_out_fd = dup(fileno(stdout));
    save_out_fd_access(save_out_fd);

    if (-1 == dup2(out_fd, fileno(stdout))) {
        perror("cannot redirect stdout");
        return;
    }
}

char *mx_end_stdout_interception() {
    fflush(stdout);
    int out_fd = out_fd_access(MX_ACCESS);
    close(out_fd);
    out_fd_access(0);

    int save_out_fd = save_out_fd_access(MX_ACCESS);
    dup2(save_out_fd, fileno(stdout));
    close(save_out_fd);
    save_out_fd_access(0);

    char *result = mx_file_to_str(MX_STDOUT_STORE);
    unlink(MX_STDOUT_STORE);

    return result;
}
