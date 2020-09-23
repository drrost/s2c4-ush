#include "libmx.h"

void mx_push_back(t_list **head, void *data) 
{
    if (head == NULL) return;
    t_list *new_node = mx_create_node(data);
    if (*head == NULL) {
        *head = new_node;
    }
    else {
        t_list *cur = NULL;
        for(cur = *head; cur->next != NULL; cur = cur->next)
            ;
        cur->next = new_node;
    }
}
