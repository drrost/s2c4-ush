#include "../inc/ush.h"
#include <stdlib.h>

//static int mx_arrlen(char **arr) {
//    int length = 0;
//
//    while (*arr) {
//        length++;
//        arr++;
//    }
//    return length;
//}

t_input *mx_parse_input(const char *str) {
    t_list *main_list = NULL;

    int i = 0;
    int start = 0;


    char **strnew = mx_strsplit(str, ';');              //TODO error ';'
    t_input *inp = (t_input *)malloc(sizeof(t_input) * mx_count_words(str, ';') + 1);
    inp->commands = NULL;
    for (; strnew[i] != NULL; i++) {                         //цикл для добавления команд;
        char *strend = strnew[i];

        while (1) {
            int end = get_logic_operator_index(strend, '&');
            char *sub = substr(strend, start, end == -1 ? mx_strlen(strend) + 1 : end);
            char *strpipe = sub;

            while (1) {
                int pipend = get_logic_operator_index(strpipe, '|');
                char *subpipe = substr(strpipe, start, pipend == -1 ? mx_strlen(strpipe) + 1 : pipend);

                if (pipend > 0)
                    strpipe += pipend + 2;
                t_command *command = mx_command_new();
                char **split = mx_strsplit(subpipe, ' ');
                command->name = split[0];
                if (split[1] != NULL)
                    command->arguments = split[1];
                else
                    command->arguments = NULL;
                command->stop_on_fail = pipend == -1 ? true : false;    // Если наталкиваемся на пайп (pipend != -1), значит это либо последняя команда в серии пайпов
                mx_push_back(&inp->commands, command);                       // либо команда без пайпов. Для таких команд в случае ошибки нужно остановить выполнение,
                if (pipend == -1)
                    break;
                mx_del_strarr(&split);
            }
            strend += end + 2;
            if (end == -1)
                break;                                                // TODO  записывать результат в структуру (лист)
        }
        mx_push_back(&main_list, inp);
    }
    return inp;
}
