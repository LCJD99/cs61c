#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    if (head == NULL) {
        return 0;
    } 
    node *tortoise = head, *hare = head;
    while(hare->next && hare->next->next) {
        tortoise = tortoise->next;
        hare = hare->next->next;
        if (tortoise == hare) {
            return 1;
        }
    }
    
    return 0;
}