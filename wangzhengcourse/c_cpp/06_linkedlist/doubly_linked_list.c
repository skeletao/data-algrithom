/*
 * Doubly linked list:
 *     1. data type is fixed as int
 * 
 * Functions: 
 *     1. push/append/insert
 *     2. delete 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dnode {
    int data;
    struct dnode *prev;
    struct dnode *next;
};

/* add node at the start */
void push(struct dnode **head_ref, struct dnode *node)
{
    if (*head_ref)
    {
        (*head_ref)->prev = node;
    }
    node->next = *head_ref;
    *head_ref = node;
}

/* add node at the end */
void append(struct dnode **head_ref, struct dnode *node)
{
    struct dnode *head = *head_ref;
    if (*head_ref == NULL)
    {
        *head_ref = node;
    } else
    {
        while (head->next) head = head->next;
        node->prev = head;
        head->next = node;
    }
}

/* add node after prev */
void insert(struct dnode *prev, struct dnode* node)
{
    if (prev == NULL)
    {
        printf("Previous node should not be NULL");
        return;
    }
    node->prev = prev;
    node->next = prev->next;
    prev->next = node;
    if (node->next) node->next->prev = node;
}

/* delete current node */
void delete1(struct dnode **head_ref, struct dnode *node)
{
    struct dnode *head = *head_ref;

    if (*head_ref == NULL) return;

    if (node == *head_ref)
    {
        *head_ref = node->next;
    } 
    
    if (node->next)
    {
        node->next->prev = node->prev; 
    }

    if (node->prev)
    {
        node->prev->next = node->next;
    }

    free(node);
}

void print_dlist(struct dnode* head)
{
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\r\n");
}

struct dnode* creat_dnode(int val)
{
    struct dnode* node = (struct dnode*)malloc(sizeof(struct dnode));
    node->data = val;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

int main(void)
{
    struct dnode *head = NULL;
    
    push(&head, creat_dnode(2));
    push(&head, creat_dnode(4));
    push(&head, creat_dnode(8));
    push(&head, creat_dnode(10));
    print_dlist(head);

    append(&head, creat_dnode(12));
    append(&head, creat_dnode(14));
    print_dlist(head);

    insert(head->next, creat_dnode(6));
    print_dlist(head);

    delete1(&head, head);
    delete1(&head, head->next);
    print_dlist(head);
    
    return 0;
}