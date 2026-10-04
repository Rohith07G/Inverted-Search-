
#include "header.h"

main_node *hash_table[27]; // Global hash table array with 27 indices (a-z + non-alphabetic)

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("ERROR: Missing Files\n");
        printf("Usage:\n <./a.out> <file1.txt> <file2.txt> ...\n");
        return FAILURE;
    }

    Slist *head = NULL;

    for(int i = 1; i < argc; i++)
    {
        if(extension(argv[i]) == FAILURE)
        {
            continue;
        }

        if(empty(argv[i]) == FAILURE)
        {
            continue;
        }

        if(duplicate(head, argv[i]) == FAILURE)
        {
            printf("File %s is a duplicate file\n", argv[i]);
            continue;
        }

        if(insert_at_last(&head, argv[i]) == FAILURE)
        {
            continue;
        }

        printf("File %s added to the linked list\n", argv[i]);
    }

    print_list(head);

    int option, flag = 0, count = 0;

    while(1)
    {
        printf("\n---------------------------------------------------------------\n");
        printf("           INVERTED SEARCH ENGINE - MAIN MENU\n");
        printf("---------------------------------------------------------------\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Update Database\n");
        printf("4. Search Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("Enter your option : ");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                if(flag == 0)
                {
                    flag = 1;
                    if(create_database(head, hash_table) == SUCCESS)
                    {
                        printf("\nSUCCESS: Files added to database successfully!\n");
                    }
                    else
                    {
                        printf("\nFAILURE: Files not added to database successfully!\n");
                    }
                }
                else
                {
                    printf("\nWARNING: Database creation already completed!\n");
                }
                break;

            case 2:
                if(display_database(hash_table) == SUCCESS)
                {
                    printf("\nData displayed successfully\n");
                }
                else
                {
                    printf("\nData not displayed\n");
                }
                break;
            
        }

           
    }
}
