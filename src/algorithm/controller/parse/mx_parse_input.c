//
// Created by Nadiia Onopriienko on 10/3/20.
//

#include <ush.h>

static char *substr(const char *src, int start, int end) {
    char *result = (char *)malloc(end - start + 1);
    int iter = 0;

    for (int i = start; i < end && src[i] != '\0'; i++) {
        result[iter++] = src[i];
    }
    result[iter] = '\0';
    return result;
}

int get_logic_operator_index(const char *str, char operator) {
    if (str) {
        for (int j = 0; str[j] != '\0'; j++) {
            if (str[j] == operator && str[j + 1] == operator
                && j > 0 && str[j - 1] != '\\')
                return j;
        }
    }
    return -1;
}

t_input *mx_parse_input(const char *input) {
    t_list *main_list = NULL;

    int i = 0;
    int start = 0;

    char **strnew = mx_strsplit(input, ';');              //TODO error ';'

    // цикл для добавления команд
    for (; strnew[i] != NULL; i++) {
        t_input *inp = (t_input *)malloc(
            sizeof(t_input) * mx_count_words(input, ';') + 1);
        inp->commands = NULL;
        char *strend = strnew[i];

        while (1) {
            int end = get_logic_operator_index(strend, '&');
            char *sub = substr(strend, start,
                               end == -1 ? mx_strlen(strend) + 1 : end);
            char *strpipe = sub;

            while (1) {
                int pipend = get_logic_operator_index(strpipe, '|');
                char *subpipe = substr(strpipe, start,
                                       pipend == -1 ? mx_strlen(strpipe) + 1
                                                    : pipend);
                if (pipend > 0)
                    strpipe += pipend + 2;
                t_command *command = mx_command_new();
                command->name = mx_strtrim(subpipe);
                command->stop_on_fail = pipend == -1 ? true
                                                     : false;    // Если наталкиваемся на пайп (pipend != -1), значит это либо последняя команда в серии пайпов
                // либо команда без пайпов. Для таких команд в случае ошибки нужно остановить выполнение,
                mx_push_back(&inp->commands,
                             command);                      // то есть stop on fail = true.
                if (pipend == -1)
                    break;
            }
            strend += end + 2;
            if (end == -1)
                break;                                                // TODO  записывать результат в структуру (лист)
        }
        mx_push_back(&main_list, inp);
    }
    return main_list;
}

void execute_command(t_command *command) {
    mx_printstr("Start to execute command: ");
    mx_printstr(command->name);
    mx_printstr("\n");
}

void execute_input(t_input *input) {
    while (input->commands != NULL) {
        execute_command((t_command *)input->commands->data);
        input->commands = input->commands->next;
    }
}

void test(t_list *res) {
    while (res != NULL) {
        execute_input((t_input *)res->data);
        res = res->next;
    }
}
