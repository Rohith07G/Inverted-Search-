#include "header.h"

int extension(char *filename)
{
    char *ext = strstr(filename, ".");

    if (ext != NULL && strcmp(ext, ".txt") == 0)
    {
        return SUCCESS;
    }
    else
    {
        printf("File %s is not a .txt file\n", filename);
        return FAILURE;
    }
}

int empty(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("ERROR: Cannot open file %s\n", filename);
        return FAILURE;
    }
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) != 0)
    {
        fseek(fp, 0, SEEK_SET);
        return SUCCESS;
    }
    printf("ERROR: No content present in file %s\n", filename);
    return FAILURE;
}

int insert_at_last(Slist **head, char *file)
{
    Slist *new = malloc(sizeof(Slist));
    if (new == NULL)
    {
        return FAILURE;
    }

    strcpy(new->file, file);
    new->link = NULL;
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    Slist *temp = *head;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}

int duplicate(Slist *head, char *filename)
{
    while (head != NULL)
    {
        if (strcmp(head->file, filename) == 0)
        {
            return FAILURE;
        }
        head = head->link;
    }
    return SUCCESS;
}

void print_list(Slist *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    size_t max_len = 0;
    Slist *temp = head;

    while (temp != NULL)
    {
        size_t len = strlen(temp->file);
        if (len > max_len)
        {
            max_len = len;
        }
        temp = temp->link;
    }

    if (max_len < 8)
        max_len = 8;

    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("              FILES CURRENTLY IN THE LIST\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("  No. │  %-*s\n", (int)max_len, "File Name");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    int index = 1;
    temp = head;

    while (temp != NULL)
    {
        printf("  %-3d │  %-*s\n", index++, (int)max_len, temp->file);
        temp = temp->link;
    }
    printf("\n");
}