#include "header.h"   

int display_database(main_node*  *hash_table)  
{
    size_t max_word_len = strlen("Word");
    size_t max_file_len = strlen("File Name");
    int has_data = 0;

    for (int i = 0; i < 27; i++)
    {
        main_node *tempmain = hash_table[i];
        while (tempmain != NULL)
        {
            has_data = 1;

            size_t word_len = strlen(tempmain->word);
            if (word_len > max_word_len)
            {
                max_word_len = word_len;
            }

            sub_node *tempsub = tempmain->link;
            while (tempsub != NULL)
            {
                size_t file_len = strlen(tempsub->file_name);
                if (file_len > max_file_len)
                {
                    max_file_len = file_len;
                }
                tempsub = tempsub->link;
            }
            tempmain = tempmain->mainlink;
        }
    }

    if (!has_data)
    {
        printf("\nWARNING: Database is empty!\n");
        return SUCCESS;
    }

    if (max_word_len < 4)  max_word_len = 4;
    if (max_file_len < 9)  max_file_len = 9;

    int index_width = 7;
    int word_width = (int)max_word_len;
    int file_count_width = 12;
    int file_name_width = (int)max_file_len;
    int word_count_width = 12;

    int total_width = index_width + 3 + word_width + 3 + file_count_width + 3 + file_name_width + 3 + word_count_width;

    printf("\n");
    for (int i = 0; i < total_width; i++) printf("-");
    printf("\n");

    printf("                      DATABASE CONTENTS\n");

    for (int i = 0; i < total_width; i++) printf("-");
    printf("\n");

    printf("%-*s │ %-*s │ %-*s │ %-*s │ %-*s\n", index_width, "Index", word_width, "Word", file_count_width, "File Count", file_name_width, "File Name", word_count_width, "Word Count");

    for (int i = 0; i < total_width; i++) printf("-");
    printf("\n");

    for (int i = 0; i < 27; i++)
    {
        main_node *tempmain = hash_table[i];
        while (tempmain != NULL)
        {
            sub_node *tempsub = tempmain->link;
            int first_entry = 1;

            while (tempsub != NULL)
            {
                if (first_entry)
                {
                    printf("%-*d │ %-*s │ %-*d │ %-*s │ %-*d\n",index_width, i, word_width, tempmain->word, file_count_width, tempmain->file_count, file_name_width, tempsub->file_name, word_count_width, tempsub->word_count);
                    first_entry = 0;
                }
                else
                {
                    printf("%-*s │ %-*s │ %-*s │ %-*s │ %-*d\n", index_width, "",word_width, "",file_count_width, "",file_name_width, tempsub->file_name, word_count_width, tempsub->word_count);
                }
                tempsub = tempsub->link;
            }
            tempmain = tempmain->mainlink;
        }
    }

    return SUCCESS;
}
