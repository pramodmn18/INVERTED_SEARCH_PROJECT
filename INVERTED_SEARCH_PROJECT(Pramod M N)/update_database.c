#include "inverted.h"

int store_file_names(fname **head, char *filename)
{
    fname *new;
    //allocate memory for file name
   if((new =  malloc(sizeof(fname))) == NULL)
       return FAILURE;
   //copy file name
   strcpy(new->argv_file,filename);
   new->link = NULL;

   //when no file name exist
   if(*head == NULL)
   {
       *head = new;
	   return SUCCESS;
   }
   fname *temp = *head;
   
   //run till last
   while(temp->link != NULL)
   {
       temp = temp->link;
   }

   //update link
   temp->link = new;

   return SUCCESS;
}


