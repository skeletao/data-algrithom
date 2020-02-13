/*
 * Circular single linked list:
 *     1. data type is fixed as int
 * 
 * Functions: 
 *     1. insert
 *     2. delete 
 *     3. traverse
 */

#include <stdio.h>
#include <stdlib.h>

struct cnode {
    int data;
    struct cnode *next;
};

void insert(struct cnode **head_ref, struct cnode *node)
{
    struct cnode *head = *head_ref;
    
    if (head == NULL)
    {
        *head_ref = node;
        node->next = node;
    } else
    {
        node->next = head->next;
        head->next = node;
    }
}


void delete1(struct cnode **head_ref, struct cnode *node)
{
    struct cnode *head = *head_ref;
    struct cnode *prev = head;

    if (head == NULL) return;

    if (head == node)
    {
        if (head->next == head)
        {
            *head_ref = NULL;
        } else
        {
            while (prev->next != head) prev = prev->next;
            prev->next = node->next;
            free(node);
            *head_ref = prev;
        }
    } 
    else
    {
        do
        {
            if (head == node)
            {
                prev->next = head->next;
                free(node);
                break;
            }
            prev = head;
            head = head->next;
        } while (head != *head_ref);
    }
}


void traverse(struct cnode **head_ref)
{
    struct cnode *tmp = *head_ref;
    if (tmp) 
    {
        do
        {
            printf("%d ", tmp->data);
            tmp = tmp->next;
        } while (tmp!= *head_ref);
        
    }
    printf("\r\n");
}


struct cnode* create_node(int val)
{
    struct cnode* node = (struct cnode*)malloc(sizeof(struct cnode));
    node->data = val;
    node->next = NULL;
    return node;
}


int main() 
{ 
    /* Initialize lists as empty */
    struct cnode* head = NULL; 
  
    /* Created linked list will be 2->5->7->8->10 */
    struct cnode* n1 = create_node(2); 
    struct cnode* n2 = create_node(5); 
    struct cnode* n3 = create_node(7); 

    insert(&head, n1); 
    insert(&head, n2); 
    insert(&head, n3); 

  
    printf("List Before Deletion: "); 
    traverse(&head); 
  
    delete1(&head, n1); 
    delete1(&head, n3); 
    printf("List After Deletion1: "); 
    traverse(&head); 
    delete1(&head, n2); 
    printf("List After Deletion2: "); 
    traverse(&head); 
  
    return 0; 
}