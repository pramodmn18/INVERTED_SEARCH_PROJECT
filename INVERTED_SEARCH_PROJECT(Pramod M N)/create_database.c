#include "inverted.h"
int create_database(node **head,char *word,char *filename)
{
    extern int largest_word;
    int len = strlen(word);
    //largest word in data
    if(largest_word < len)
	largest_word = len;
   // printf("%s\n",word);
    if(*head == NULL)
    {
	node *new=malloc(sizeof(node));
	new->file_count=1;
	strcpy(new->word,word);
	table *newtable=malloc(sizeof(table));
	newtable->word_count=1;
	newtable->link=NULL;
	strcpy(newtable->f_name,filename);
	new->table=newtable;
	new->link=NULL;
	*head=new;
	return SUCCESS;
    }
    node *temp=*head;

    while(temp != NULL)
    {
	//word is same and file name same
	

	if(strcmp(temp->word, word) == 0)
	{
	    table *temp1 = temp->table;
	    while(temp1 != NULL)
	    {

		if(strcasecmp(temp1->f_name,filename) == 0)
		{
		    temp1->word_count += 1;
		    return SUCCESS;
		}
		if(temp1->link == NULL)
		{
		    table *newtable;

		    if((newtable = malloc(sizeof(table))) != NULL)
		    {
			newtable->word_count = 1;
			strcpy(newtable->f_name, filename);
			temp->file_count += 1;
			newtable->link = NULL;
			temp1->link = newtable;
			return SUCCESS;
		    }
		}
		temp1 = temp1->link;
	    }

	}
	//word is same file name is not same
	if(temp->link == NULL)
	{
	    node *new=malloc(sizeof(node));
	    table *newtable=malloc(sizeof(table));
	    newtable->word_count=1;
	    newtable->link=NULL;
	    strcpy(newtable->f_name,filename);
	    strcpy(new->word,word);
	    new->table=newtable;
	    new->file_count = 1;
	    new->link=NULL;
	    temp->link=new;
	    return SUCCESS;
	}
	temp=temp->link;
    }
}



