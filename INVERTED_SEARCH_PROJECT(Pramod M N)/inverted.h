#ifndef INVERTED_H
#define INVERTED_H

#define WORD_SIZE 50
#define FNAME_SIZE 50
#define SUCCESS 1
#define FAILURE -1
#define DUPLICATE -2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include <errno.h>

typedef struct sub
{
		int word_count;
		char f_name[FNAME_SIZE];
		struct sub *link;
}table;

typedef struct command_line_file
{
    char argv_file[FNAME_SIZE];
    struct command_line_file *link;
}fname;

typedef struct mainnode
{
		int file_count;
		char word[WORD_SIZE];
		struct mainnode *link;
		struct sub *table;
} node;

int create_database(node **, char *, char *);
int print(node *head,int);
node *search(node *, char *);
int store_file_names(fname **, char *);
int check_duplicate(fname *, char *);
int save_database(node *head, char *, FILE **);
#endif

