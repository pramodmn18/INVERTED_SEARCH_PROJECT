#include "inverted.h"

int save_database(node *head, char * file, FILE **fptr)
{
    //open destination file
    int index;
    char temp1[WORD_SIZE];

    //validate destination file is open
    // if(fptr == NULL)
    //return FAILURE;
    //when database is not created
    
    while(head != NULL)
    {
	strcpy(temp1, head->word);
	if(islower(temp1[0]))
	    index=temp1[0]%97;
	else
	    index=temp1[0]%65;
	fprintf(*fptr,"%c %d",'#',index);
	//fwrite(&index,sizeof(index),1,*fptr);
	fprintf(*fptr,"\n%s;%d;",temp1,head->file_count);
	table *temp=head->table;
	while(temp != NULL)
	{
	fprintf(*fptr,"%s;%d%c\n",temp->f_name,temp->word_count,'#');
	   temp=temp->link;
	}
	head=head->link;
    }
    return SUCCESS;
}


