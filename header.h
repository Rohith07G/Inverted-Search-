#ifndef HEAD_H
#define HEAD_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define SUCCESS  0 
#define FAILURE -1


typedef struct sub 
{
    char words[100];        // Array to store word
    int word_count;         // Count of word occurrences in file
    char file_name[30];     // Array to store filename
	struct sub *link;       // Pointer to next sub node
}sub_node;                  // Type name for sub node structure
typedef struct single       // Structure definition for single linked list node (stores file list)
{
	char file[30];          // Array to store filename
	struct single *link;    // Pointer to next node
}Slist;                     // Type name for single linked list node
typedef struct hash         // Structure definition for hash table
{
    int index;              // Hash table index
    struct main *link;      // Pointer to main node
}Hash;                      // Type name for hash structure
typedef struct main         // Structure definition for main node (stores word information)
{
	int file_count;         // Number of files containing the word
    char word[100];          // Array to store word
    char file[20][30];      // 2D array to store filenames
	struct sub *link;       // Pointer to sub node
    struct main *mainlink;  // Pointer to next main node
}main_node;                 // Type name for main node structure


int create_database(Slist*head,main_node* hash_table[]);
int display_database(main_node* hash_table[]); 



#endif