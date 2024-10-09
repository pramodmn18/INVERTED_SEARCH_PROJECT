#include "inverted.h"

int largest_word = 0;

//this is to avoid multiple time same database creation  when set imply database not created  when reset imply data base already created
static int database_not_created = 1;

int main(int argc,char **argv)
{
    node *head[26]={NULL}, *temp_node = NULL;
    fname *head_name = NULL;
    int index, ret,i;

    
    if(argc < 2)   //validate number of cmd line arguments
    {
	printf("INFO : Try again and pass file(s) to command line argument\n");
	exit(0);

    }

 
    for(int i = 1; i < argc; i++)
    {
	ret = store_file_names(&head_name, argv[i]);    //create data for file names to check duplicate

	if(ret == FAILURE)
	{
	    printf("ERROR! Some problem occured while storing file(s) name, skippin file...\n");
	    continue;
	}
    }

    while(1)
    {
	char *target = NULL;
	//initialize choice to avoid unwanted choice selection
	int choice = -1;
	printf("1)Create Database\n2)Print\n3)Search\n4)Update Database\n5)Save Database\n6)Exit\nChoice : ");
	scanf("%d",&choice);
	getchar();
	switch(choice)
	{
	    case 1:
		{
		    fname *fname_temp = head_name;
		    //run loop for all file passed through cmd line
		    for(i=1; i < argc && database_not_created;i ++)
		    {
			FILE *fptr=fopen(argv[i],"r");

			//when file does not exist
			if(fptr == NULL)
			{
			    //print error
			    printf("%s %s\n",argv[i],strerror(errno));
			    //check more file availabe to create database
			    if(i < argc - 1)
				continue;
			    //exit when only 1 file passed via cmd line and it does not exist
			    else
				exit(1);
			}

			//check duplicate file and skip database creation
			    if(check_duplicate(fname_temp, NULL)==DUPLICATE)
			    {
			    printf("INFO! Duplicate found for file %s, skipping...\n",argv[i]);
				fname_temp = fname_temp->link;
				continue;
			    }
			 //move offset to end
			fseek(fptr,0,SEEK_END);
			
			//get file size
			int size=ftell(fptr);
			fseek(fptr,0,SEEK_SET);
			
			char *data;
			if((data = calloc(size+1,1)) == NULL)
			{
			    printf("ERROR! Insufficient Storage\n");
			    exit(1);
			}

			//read data from file
			fread(data,size,1,fptr);
			data[size] = '\0';

			//create a pointr to store word
			char *temp=strtok(data,"\"\n\t ");
			while(temp != NULL)
			{
			    //get index of main array
			    if(islower(temp[0]))
				index=temp[0]%97;
			    else
				index=temp[0]%65;
			    //call create data base function
			    ret = create_database(&head[index],temp,argv[i]);
			    temp=strtok(NULL,"\"\n\t ");
			}
			//close file
			fclose(fptr);
		    }
		    //reset to indicate database already created
		    database_not_created = 0;
		}
		if(ret == SUCCESS)
		    printf("INFO! Database created successfully\n");
		break;
	    case 2:
		for (i=0;i<26;i++)
		    print(head[i], 0);
		break;

	    case 3:
		//get memory for target word
		if(( target = malloc(20*sizeof(char))) != NULL)
		{
		    printf("Enter word to be searched : ");
		    scanf("%s",target);
		    getchar();
		}
		//get index for word
		if(islower(target[0]))
		    index=target[0]%97;
		else
		    index=target[0]%65;
		//search the target word
		temp_node = search(head[index],target);
		
		if( temp_node == NULL)
		{
		    printf("INFO : Data not found\n");
		}
		print(temp_node, 1);
		
		free(target);
		break;
	    case 4:
		{
		    //create array for file name
		    char file[20];
		    //read file name
		    printf("Enter file name : ");
		    scanf("%s",file);
		    getchar();

		    //check duplicate 
		    if((ret = check_duplicate(head_name,file)) == DUPLICATE)
		    {
			printf("INFO! File %s already exist in database\n",file);
			break;
		    }
		    
		    //store filne name in file data
		    if((ret = store_file_names(&head_name,file)) == FAILURE)
		    {
			printf("ERROR! Some problem occured while storing file(s) name, try again\n");
			break;
		    }

		    //open file
		    FILE *fptr=fopen(file,"r");

		    //if file not exist
		    if(fptr == NULL)
		    {
			printf("%s %s\n",file,strerror(errno));
			break;
		    }
		    //move offset to end
		    fseek(fptr,0,SEEK_END);
		    //get file size
		    int size=ftell(fptr);
		    //reset offset
		    fseek(fptr,0,SEEK_SET);
		    //get memory to store word
		    char *data;
		    if((data = calloc(size+1,1)) == NULL)
		    {
			printf("\033[;31mERROR! Insufficient Storage\033[;0m\n");
			exit(1);
		    }
		    //read data from file and store in data
		    fread(data,size,1,fptr);
		    data[size] = '\0';

		    //get the word
		    char *temp=strtok(data,"\"\n\t ");
		    while(temp != NULL)
		    {
			//get index for word
			if(islower(temp[0]))
			    index=temp[0]%97;
			else
			    index=temp[0]%65;
			ret = create_database(&head[index],temp,file);
			temp=strtok(NULL,"\"\n\t ");

		    }
		}
		if(ret == SUCCESS)
		    printf("INFO! Database updated successfully\n");
		break;
	    case 5:
		{
		    //create  array for file name
		    char file[20];
		    //read file name
		    printf("Enter file name : ");
		    scanf("%s",file);
		    printf("\033[;0m");
		    getchar();
		    //open file write + read mode
		    FILE *fptr = fopen(file,"w+");
		    //run loop for all indese
		    for(int i = 1; i < 26; i++)
		    {
			//when head is null i.e word is not present for the index 
			if(head[i] == NULL)
			    continue;

			if( ( ret = save_database(head[i],file,&fptr))  == FAILURE )
			{
			    printf("ERROR! Unable to save database, try again\n");
			    break;
			}

		    }
		    fclose(fptr);

		    if(ret == SUCCESS)
			printf("INFO! Database saved successfully\n");
		}
		break;

	    case 6:
		exit(0);
	    default :
		printf("INFO! Invalid Choice\n");
		
	}
	printf("\033[;34m********************************************************\033[;0m\n");
    }
}

