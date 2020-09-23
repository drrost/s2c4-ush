#include "libmx.h"

void mx_pop_front(t_list **head) 
{
    if (head == NULL) return;
    if (*head == NULL) return;

    t_list *tList = *head;
    *head = (*head)->next;
    free(tList);
}
