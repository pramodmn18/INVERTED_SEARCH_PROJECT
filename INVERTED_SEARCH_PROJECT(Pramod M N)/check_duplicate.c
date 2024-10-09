#include "inverted.h"

int check_duplicate(fname *head, char *str)
{
    fname *temp;
    char name[FNAME_SIZE];
    if(str != NULL)
	strcpy(name, str);

    while(head != NULL)
    {
	if(str == NULL)
	{
	    strcpy(name,head->argv_file);
	    temp = head->link;
	}
	else
	{
	temp = head;
	}
       while(temp != NULL)
       {
	   if(strcmp(name, temp->argv_file) == 0)
	   {
	       return DUPLICATE;
	   }
	   temp = temp->link;
       }
       head = head->link;
    }
    return SUCCESS;
}



