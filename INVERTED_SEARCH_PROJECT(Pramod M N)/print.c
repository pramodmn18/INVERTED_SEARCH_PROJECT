#include "inverted.h"
int print(node *head, int flag)
{
    //largest word length
    extern int largest_word;
    if(head == NULL)
    {
	return 0;
    }
    //run over all words index
    while(head )
    {
	printf("[%-*s]\t",largest_word,head->word);
	printf(" %d file(s) : ",head->file_count);
	table *temp=head->table;
	//run over all table under a word
	while(temp)
	{
	    printf("%s : ",temp->f_name);
	    printf("%d time(s) : ",temp->word_count);
	    temp=temp->link;
	}
	head=head->link;
	//printf("\b\b  \033[;0m\n");
	printf("\n");
	
	//flag = 1 for printing when only 1 word info need to be printed
	if(flag == 1)
	    break;
    }
}



