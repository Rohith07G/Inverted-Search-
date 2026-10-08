#include "header.h"   

int hash_function(char *word)   
{
    int index;
    if (isalpha(word[0]))
        index = tolower(word[0]) - 'a';
    else
        index = 26;

    return index;
}

int update_database(Slist **head, main_node *hash_table[], char *file)   
{
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL)
    {
        printf("ERROR: Cannot open file %s\n", file);
        return FAILURE;
    }

    fseek(fptr, 0, SEEK_END);
    long length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char *data = malloc(length + 2);
    fread(data, 1, length, fptr);
    data[length] = '\0';
    fclose(fptr);

    if (data[length - 1] == '\n')
    {
        data[length - 1] = '\0';
        length--;
    }

    if (data[0] != '#' || data[length - 1] != '#')
    {
        printf("ERROR: File must start and end with '#'\n");
        free(data);
        return FAILURE;
    }

    char *ptr = data + 1;

    while (*ptr)
    {
        char *end = strchr(ptr, '#');
        if (!end)
            break;

        *end = '\0';

        int index;
        char word[27];

        if (sscanf(ptr, "%d;%26[^;];", &index, word) != 2)
        {
            ptr = end + 1;
            continue;
        }

        char *fp = strchr(ptr, ';');
        if (!fp)
        {
            ptr = end + 1;
            continue;
        }

        fp = strchr(fp + 1, ';');
        if (!fp)
        {
            ptr = end + 1;
            continue;
        }
        fp++;

        while (*fp && fp < end)
        {
            int wc = 0;
            char fname[30] = {0};
            int n = 0;

            sscanf(fp, "%1d%29[^;]%n", &wc, fname, &n);
            if (n == 0)
                break;

            fp += n;
            if (*fp == ';')
                fp++;

            int hash_index = index;
            main_node *temp = hash_table[hash_index];
            main_node *found = NULL;

            while (temp)
            {
                if (strcmp(temp->word, word) == 0)
                {
                    found = temp;
                    break;
                }
                temp = temp->mainlink;
            }

            if (found)
            {
                int exists = 0;

                for (int j = 0; j < found->file_count; j++)
                {
                    if (strcmp(found->file[j], fname) == 0)
                    {
                        exists = 1;
                        break;
                    }
                }

                if (!exists)
                {
                    strcpy(found->file[found->file_count], fname);
                    found->file_count++;

                    sub_node *new_sub = malloc(sizeof(sub_node));
                    strcpy(new_sub->file_name, fname);
                    strcpy(new_sub->words, word);
                    new_sub->word_count = wc;
                    new_sub->link = found->link;
                    found->link = new_sub;
                }
            }
            else
            {
                main_node *new = malloc(sizeof(main_node));
                strcpy(new->word, word);
                new->file_count = 1;
                strcpy(new->file[0], fname);
                new->link = NULL;

                sub_node *new_sub = malloc(sizeof(sub_node));
                strcpy(new_sub->file_name, fname);
                strcpy(new_sub->words, word);
                new_sub->word_count = wc;
                new_sub->link = NULL;

                new->link = new_sub;
                new->mainlink = hash_table[hash_index];
                hash_table[hash_index] = new;
            }

            delete_file_from_list(head, fname);
        }

        ptr = end + 1;
    }

    free(data);

    if (*head != NULL)
    {
        create_database(*head, hash_table);
    }

    printf("Data updated successfully\n");
    return SUCCESS;
}

void delete_file_from_list(Slist **head, char *filename)   
{
    Slist *temp = *head;
    Slist *prev = NULL;

    while (temp)
    {
        if (strcmp(temp->file, filename) == 0)
        {
            if (prev == NULL)
                *head = temp->link;
            else
                prev->link = temp->link;

            free(temp);
            return;
        }
        prev = temp;
        temp = temp->link;
    }
}
