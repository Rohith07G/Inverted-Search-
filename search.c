#include "header.h" 

int search_database(main_node* hash_table[])   
{
    char key[50];   
    printf("Enter the search word : ");
    scanf("%s", key);
    int index, found = 0;
    if (isalpha(key[0]))
    {
        index = tolower(key[0]) - 97;   // a=0, b=1, ...
    }
    else
    {
        index = 26;   // Non-alphabetic characters
    }

    main_node *tempmain = hash_table[index];
    while (tempmain != NULL)
    {
        if (strcmp(tempmain->word, key) == 0)
        {
            found = 1;
            sub_node *tempsub = tempmain->link;

            printf("\n---------------------------------------------------------------\n");
            printf("SEARCH RESULTS: Word \"%s\" found in:\n", tempmain->word);
            printf("---------------------------------------------------------------\n");

            while (tempsub != NULL)
            {
                printf("  %s\n", tempsub->file_name);
                tempsub = tempsub->link;
            }
        }
        tempmain = tempmain->mainlink;
    }

    if (!found)
    {
        return FAILURE;
    }
    return SUCCESS;
}
