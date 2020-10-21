//
// Created by Karina Barinova on 20.10.2020.
//

#include <ush.h>

int mx_about(void) {
    char *about = "           _.-''|''-._\n        .-'     |     `-.\n      .'\\       |       /`.\n    .'   \\      |      /   `.        USHELL Made by\n";
    char *about1 = "    \\     \\     |     /     /\n     `\\    \\    |    /    /'         @Nadiia Onopriienko\n";
    char *about2 = "       `\\   \\   |   /   /'           @Rostyslav Druzhchenko\n         `\\  \\  |  /  /'             @Karina Barinova\n";
    char *about3 = "        _.-`\\ \\ | / /'-._ \n       {_____`\\\\|//'_____}\n               `-'\n\n";
    mx_printstr(about);
    mx_printstr(about1);
    mx_printstr(about2);
    mx_printstr(about3);
    return 0;
}
