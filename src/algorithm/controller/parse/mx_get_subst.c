#include "../inc/ush.h"

bool get_subst(const char *str) {
    bool start1;
    bool start2;

    if (str == NULL)
        return false;

    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == '$' && str[i + 1] == '(') {
            start1 = true;
        }
        else if(start1 && str[i] == ')') {
            return true;
        }
        else if(!start1  && str[i] == '`') {
            start2 = true;
        }
        else if(start2  && str[i] == '`') {
            return true;
        }
    }
    return false;
}

