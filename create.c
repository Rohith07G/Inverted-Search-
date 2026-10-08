#include "header.h"

static int add_word_to_hash(const char *word, const char *filename, main_node *hash_table[])
{
    if (word[0] == '\0')
    {
        return SUCCESS;
    }

    int index;

    if (isalpha(word[0]))
    {
        index = tolower(word[0]) - 'a';
    }
    else
    {
        index = 26;
    }

    main_node *hashtemp = hash_table[index];
    main_node *prev_main = NULL;

    if (hashtemp == NULL)
    {
        main_node *Main = malloc(sizeof(main_node));

        if (Main == NULL)
        {
            return FAILURE;
        }

        strcpy(Main->word, word);
        Main->file_count = 1;
        Main->mainlink = NULL;

        sub_node *Sub = malloc(sizeof(sub_node));

        if (Sub == NULL)
        {
            return FAILURE;
        }

        strcpy(Sub->words, word);
        strcpy(Sub->file_name, filename);
        Sub->word_count = 1;
        Sub->link = NULL;

        Main->link = Sub;
        hash_table[index] = Main;

        return SUCCESS;
    }

    int found = 0;

    while (hashtemp != NULL)
    {
        if (strcmp(hashtemp->word, word) == 0)
        {
            sub_node *sub = hashtemp->link;
            sub_node *prev = NULL;

            while (sub != NULL)
            {
                if (strcmp(sub->file_name, filename) == 0)
                {
                    sub->word_count += 1;
                    found = 1;
                    break;
                }

                prev = sub;
                sub = sub->link;
            }

            if (!found)
            {
                sub_node *Sub = malloc(sizeof(sub_node));

                if (Sub == NULL)
                {
                    return FAILURE;
                }

                strcpy(Sub->words, word);
                strcpy(Sub->file_name, filename);
                Sub->word_count = 1;
                Sub->link = NULL;

                if (prev == NULL)
                {
                    hashtemp->link = Sub;
                }
                else
                {
                    prev->link = Sub;
                }

                hashtemp->file_count += 1;
            }

            found = 1;
            break;
        }

        prev_main = hashtemp;
        hashtemp = hashtemp->mainlink;
    }

    if (!found && prev_main != NULL && hashtemp == NULL)
    {
        main_node *Main = malloc(sizeof(main_node));

        if (Main == NULL)
        {
            return FAILURE;
        }

        strcpy(Main->word, word);
        Main->file_count = 1;
        Main->mainlink = NULL;

        sub_node *Sub = malloc(sizeof(sub_node));

        if (Sub == NULL)
        {
            return FAILURE;
        }

        strcpy(Sub->words, word);
        strcpy(Sub->file_name, filename);
        Sub->word_count = 1;
        Sub->link = NULL;

        Main->link = Sub;
        prev_main->mainlink = Main;
    }

    return SUCCESS;
}

int create_database(Slist *head, main_node *hash_table[])
{
    Slist *temp = head;

    while (temp != NULL)
    {
        FILE *fp = fopen(temp->file, "r");

        if (fp == NULL)
        {
            printf("Error opening file %s \n", temp->file);
            temp = temp->link;
            continue;
        }

        fseek(fp, 0, SEEK_SET);

        char buffer[100];

        while (fscanf(fp, "%99s", buffer) == 1)
        {
            char *ptr = buffer;

            while (*ptr != '\0')
            {
                while (*ptr != '\0' && !isalnum((unsigned char)*ptr))
                {
                    ptr++;
                }

                if (*ptr == '\0')
                {
                    break;
                }

                char word[100];
                int idx = 0;

                while (*ptr != '\0' &&  isalnum((unsigned char)*ptr) && idx < 99)
                {
                    word[idx++] = *ptr;
                    ptr++;
                }

                word[idx] = '\0';

                if (add_word_to_hash(word, temp->file, hash_table) == FAILURE)
                {
                    fclose(fp);
                    return FAILURE;
                }
            }
        }

        fclose(fp);
        temp = temp->link;
    }

    return SUCCESS;
}