//
// Created by Rostyslav Druzhchenko on 24.09.2020.
//

#include <ush.h>
#include <string.h>

static void print_prompt() {
    printf("u$l> ");
}

int main(int argc, const char *argv[]) {
    print_prompt();

    // begin a loop | till `exit`
    //
    // read a line
    // parse the line
    // execute the line
    // next

    char *line = mx_strnew(128);
    int i = 0;

    char ch = 0;
    while (true) {
        if (ch == '\n') {
            print_prompt();
            line[i] = 0;
            i = 0;
        }
        scanf("%c", &ch);
        if (strcmp(line, "exit\n") == 0 || strcmp(line, "exit") == 0)
            break;
        if (strstr(line, "pwd") != 0)
            mx_pwd(line);
        else
            printf("%c", ch);
        line[i] = ch;
        i++;
    }
    mx_strdel(&line);
    check_leaks();

    argc++;
    argv++;
    return 0;
}
