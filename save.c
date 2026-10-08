
#include "header.h"

int save_database(main_node* hash_table[], char *file)
{
    FILE *fptr = fopen(file, "w");

    if (fptr == NULL)
    {
        return FAILURE;
    }

    for (int i = 0; i < 27; i++)
    {
        main_node *tempmain = hash_table[i];
        if (tempmain == NULL)
        {
            continue;
        }

        while (tempmain != NULL)
        {
            fprintf(fptr, "#%d;%s;%d;", i, tempmain->word, tempmain->file_count);
            sub_node *tempsub = tempmain->link;

            while (tempsub != NULL)
            {
                fprintf(fptr, "%s;%d", tempsub->file_name, tempsub->word_count);
                tempsub = tempsub->link;
            }

            fprintf(fptr, "#\n");
            tempmain = tempmain->mainlink;
        }
    }

    fclose(fptr);

    return SUCCESS;
}
