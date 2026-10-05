#include "header.h"





int empty(char*filename)                                    // Function to check if file is empty
{
    FILE *fp=fopen(filename,"r");                           
    if(fp==NULL)                                            // Check if file opening failed
    {
        printf("ERROR: Cannot open file %s\n",filename);    
        return FAILURE;
    }

    fseek(fp,0,SEEK_END);                                   // Move file pointer to end of file
    if(ftell(fp) != 0 )                                     // Check if file size is zero
    {
        fseek(fp, 0, SEEK_SET );
        return SUCCESS;
    }
    printf("ERROR: No content present in file %s\n",filename);
    return FAILURE;
}



int insert_at_last(Slist **head,char *file)         // Function to insert file at end of linked list
{
    Slist *new=malloc(sizeof(Slist));               
    if(new==NULL)                                   
    {
        return FAILURE; 
    }
    strcpy(new->file,file);                         // Copy filename to new node
    new->link=NULL;                                 // Set link to NULL
    if(*head==NULL)                                 // Check if list is empty
    {
        *head=new;                                  // Set head to new node
        return SUCCESS; 
    }
    Slist *temp=*head;                              // Start from head
    while(temp->link!=NULL)                         // Traverse to last node
    {
        temp=temp->link;                            // Move to next node
    }
    temp->link=new;                                 // Link new node to last node
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






void print_list(Slist *head)            // Function to print file list
{
    if (head == NULL)                   // Check if list is empty
    {
        printf("List is empty\n");      
        return;                
    }

    size_t max_len = 0; // Variable to store maximum filename length
    Slist *temp = head; // Start from head
    while (temp != NULL) 
    {
        size_t len = strlen(temp->file); // Get length of current filename
        if (len > max_len) // Check if current length is greater
        {
            max_len = len; // Update maximum length
        }
        temp = temp->link; // Move to next node
    }
    
   
    if (max_len < 8) max_len = 8; // Minimum filename column width
    
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"); // Print separator
    printf("              FILES CURRENTLY IN THE LIST\n"); // Print header
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"); // Print separator
    printf("  No. │  %-*s\n", (int)max_len, "File Name"); // Print column headers
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"); // Print separator

    int index = 1; // Initialize index counter
    temp = head; // Start from head
    while (temp != NULL) // Traverse through list
    {
        printf("  %-3d │  %-*s\n", index++, (int)max_len, temp->file); // Print file entry with index
        temp = temp->link; // Move to next node
    }
    printf("\n");
}