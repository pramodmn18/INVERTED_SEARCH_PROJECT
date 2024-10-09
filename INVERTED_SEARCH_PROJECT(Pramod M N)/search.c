#include "inverted.h"

node *search(node *head, char *word)
{
    if(head == NULL)
	return NULL;
    //over all word index
    while(head != NULL)
    {
	if(strcasecmp(head->word,word) == 0)
	    return head;
	
	head = head->link;
    }
    return NULL;

}

