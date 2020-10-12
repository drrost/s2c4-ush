//
// Created by Rostyslav Druzhchenko on 12.10.2020.
//

#include <ush.h>

int mx_get_window_width() {
    struct winsize win;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    return win.ws_col;
}
