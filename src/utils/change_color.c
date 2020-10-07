//
// Created by Karina Barinova on 07.10.2020.
//

#include <ush.h>

#define MX_FRONT_BLACK "\033[30m"
#define MX_BACK_BLACK "\033[40m"
#define MX_FRONT_RED "\033[31m"
#define MX_BACK_RED "\033[41m"
#define MX_FRONT_GREEN "\033[32m"
#define MX_BACK_GREEN "\033[42m"
#define MX_FRONT_ORANGE "\033[33m"
#define MX_BACK_ORANGE "\033[43m"
#define MX_FRONT_BLUE "\033[34m"
#define MX_BACK_BLUE "\033[44m"
#define MX_FRONT_MAGENTA "\033[35m"
#define MX_BACK_MAGENTA "\033[45m"
#define MX_FRONT_CYAN "\033[36m"
#define MX_BACK_CYAN "\033[46m"
#define MX_FRONT_LIGHT_GREY "\033[37m"
#define MX_BACK_LIGHT_GREY "\033[47m"
#define MX_FRONT_DEFAULT "\033[39m"
#define MX_BACK_DEFAULT "\033[49m"


static void print_color_table(void) {
    printf("Foreground\tBackground\n");
    printf("%sblack\033[0m\t\t%sblack\033[0m\n", MX_FRONT_BLACK, MX_BACK_BLACK);
    printf("%sred\033[0m\t\t%sred\033[0m\n", MX_FRONT_RED, MX_BACK_RED);
    printf("%sgreen\033[0m\t\t%sgreen\033[0m\n", MX_FRONT_GREEN, MX_BACK_GREEN);
    printf("%sorange\033[0m\t\t%sorange\033[0m\n", MX_FRONT_ORANGE, MX_BACK_ORANGE);
    printf("%sblue\033[0m\t\t%sblue\033[0m\n", MX_FRONT_BLUE, MX_BACK_BLUE);
    printf("%smagenta\033[0m\t\t%smagenta\033[0m\n", MX_FRONT_MAGENTA, MX_BACK_MAGENTA);
    printf("%scyan\033[0m\t\t%scyan\033[0m\n", MX_FRONT_CYAN, MX_BACK_CYAN);
    printf("%slight-grey\033[0m\t%slight-grey\033[0m\n", MX_FRONT_LIGHT_GREY, MX_BACK_LIGHT_GREY);
    printf("%sdefault\033[0m\t\t%sdefault\033[0m\n", MX_FRONT_DEFAULT, MX_BACK_DEFAULT);
}
static void set_foreground_color(char *color) {
    if (!strcmp(color, "black"))
        printf(MX_FRONT_BLACK);
    else if (!mx_strcmp(color, "red"))
        printf(MX_FRONT_RED);
    else if (!mx_strcmp(color, "green"))
        printf(MX_FRONT_GREEN);
    else if (!mx_strcmp(color, "orange"))
        printf(MX_FRONT_ORANGE);
    else if (!mx_strcmp(color, "blue"))
        printf(MX_FRONT_BLUE);
    else if (!mx_strcmp(color, "magenta"))
        printf(MX_FRONT_MAGENTA);
    else if (!mx_strcmp(color, "cyan"))
        printf(MX_FRONT_CYAN);
    else if (!mx_strcmp(color, "lignt-grey"))
        printf(MX_FRONT_LIGHT_GREY);
    else
        printf(MX_FRONT_DEFAULT);
}
static void set_background_color(char *color) {
    if (!mx_strcmp(color, "black"))
        printf(MX_BACK_BLACK);
    else if (!mx_strcmp(color, "red"))
        printf(MX_BACK_RED);
    else if (!mx_strcmp(color, "green"))
        printf(MX_BACK_GREEN);
    else if (!mx_strcmp(color, "orange"))
        printf(MX_BACK_ORANGE);
    else if (!mx_strcmp(color, "blue"))
        printf(MX_BACK_BLUE);
    else if (!mx_strcmp(color, "magenta"))
        printf(MX_BACK_MAGENTA);
    else if (!mx_strcmp(color, "cyan"))
        printf(MX_BACK_CYAN);
    else if (!mx_strcmp(color, "lignt-grey"))
        printf(MX_BACK_LIGHT_GREY);
    else
        printf(MX_BACK_DEFAULT);
}


void color_default(void) {
    set_background_color("default");
    set_foreground_color("default");
}

int mx_change_color(char *command) {
    int index = 0;
    if (mx_strlen(command) < 1) {
        printf("usage: color [-fb color]\n");
        print_color_table();
        color_default();
        return 1;
    }

    char **arr = mx_strsplit(command, ' ');
    if (arr[index]) {
        if (mx_get_char_index(arr[index], 'f') == -1 && mx_get_char_index(arr[index], 'b') == -1) {
            printf("usage: color [-fb color]\n");
            return 1;
        }
        if (mx_get_char_index(arr[index], 'f') != -1) {
            if (arr[1])
                set_foreground_color(arr[1]);
            else
                set_foreground_color("default");
        }
        else if (mx_get_char_index(arr[index], 'b') != -1) {
            if (arr[1])
                set_background_color(arr[1]);
            else
                set_background_color("default");
        }
    }
    else {
        color_default();  
    }
    mx_del_strarr(&arr);
    return 0;
}
