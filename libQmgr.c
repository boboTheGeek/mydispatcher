/*    
 CSC521 Operating system
 Project:      2 mydispatcher
 Programmer:   Rob Miles
 Professor:    Dr. Lee
 File Created: Nov 9, 2018
 File Updated: Nov 7, 2018
 File Updated: Nov 13, 2018
 */
#include <stdlib.h>
#include "mydispatcher.h"

void appendQ(struct Process** head_ref, struct Process ** inProc){
    
    struct Process *last = *head_ref;
    struct Process *new_node = (struct Process*) malloc(sizeof(struct Process));
    new_node = *inProc;
    new_node->Qnext = NULL;                            //make this the last link
    if (*head_ref == NULL){                            //If the Linked List is empty,
        *head_ref = new_node;                          //then make the new node as head
        return;
    }
    
    while (last->Qnext != NULL){                       //loop till the last node
        last = last->Qnext;                            
    }
    last->Qnext = new_node;                             //make this the last node
	new_node->Qprev = last;                             //set reverse link
    return;
}
