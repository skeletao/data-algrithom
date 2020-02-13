/*
 * Single linked list:
 *     1. data type is fixed as int
 * 
 * Functions: 
 *     1. push/append/insert
 *     2. delete 
 *     3. reverse
 *     4. detect circle
 *     5. get middle node
 *     6. get last k-th node
 *     7. merge two sorted to one
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
    int data;
    struct node *next;
};

/* add one node at the start */
void push(struct node **head_ref, struct node *node)
{
    node->next = *head_ref;
    *head_ref = node;
}

/* add one node after prev */
void insert(struct node *prev, struct node *node)
{
    if (prev == NULL)
    {
        printf("The prvious node should not be NULL\r\n");
        return;
    }
    node->next = prev->next;
    prev->next = node;
}

/* add one node at the end */
void append(struct node **head_ref, struct node *node)
{
    struct node *head = *head_ref;
    if (head == NULL)
    {
        *head_ref = node;
    } else
    {
        while (head->next) head = head->next;
        head->next = node;
    }
}

/* delete current node, need to release current node memory */
void delete1(struct node **head_ref, struct node *node)
{
    struct node *head = *head_ref;
    struct node *prev = NULL;

    if (head == NULL) return;
    
    while (head)
    {
        if (head == node)
        {
            if (head == *head_ref) 
            {
                *head_ref = head->next;
            } else
            {
                prev->next = head->next;
            }
            free(node);
            break;
        }
        prev = head;
        head = head->next;
    }
}


/* delete current node which is not in tail, no need to release current memory */
void delete2(struct node *node)
{
    if (node->next) 
    {
        node->data = node->next->data;
        node->next = node->next->next;
        free(node->next);
    }
}

/* delete node after prev */
void delete3(struct node *prev)
{
    struct node *tmp = prev->next;
    if (tmp == NULL)
    {
        printf("The previous node should not be in the end");
        return;
    }
    prev->next = tmp->next;
    free(tmp);
}

/* reverse list */
void reverse(struct node **head_ref)
{
    struct node *head = *head_ref;
    struct node *prev = NULL, *next;

    while (head)
    {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    *head_ref = prev;
}

bool is_circle(struct node *head)
{
    struct node *slow = head, *fast = head;

    while (slow && fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

struct node* middle(struct node *head)
{
    struct node *slow = head, *fast = head;

    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct node* last_kth(struct node* head, int k)
{
    struct node *s0 = head, *s1 = head;

    while (s0 && k > 0)
    {
        s0 = s0->next;
        k--;
    }

    while (s0)
    {
        s0 = s0->next;
        s1 = s1->next;
    }

    return (k > 0)? NULL: s1;
}

/* merge two sorted linked lists to one list*/
struct node* merge(struct node *head1, struct node *head2)
{
    struct node dummy = {0, NULL};
    struct node *head = &dummy;
    
    while (1)
    {
        if (!head1)
        {
            head->next = head2;
            break;
        }

        if (!head2)
        {
            head->next = head1;
            break;
        }

        if (head1->data <= head2->data)
        {
            head->next = head1;
            head1 = head1->next;
        } else
        {
            head->next = head2;
            head2= head2->next;
        }
        head = head->next;
    }
    return dummy.next;
}

void print_list(struct node* head)
{
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\r\n");
}

struct node* creat_node(int val)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = val;
    node->next = NULL;
    return node;
}

int main(void)
{
    struct node *head = NULL;
    struct node *head1 = NULL;
    struct node *head2 = NULL;
    
    push(&head, creat_node(2));
    push(&head, creat_node(4));
    push(&head, creat_node(8));
    push(&head, creat_node(10));
    print_list(head);

    append(&head, creat_node(12));
    append(&head, creat_node(14));
    append(&head, creat_node(16));
    append(&head, creat_node(18));
    print_list(head);

    insert(head->next, creat_node(6));
    print_list(head);

    delete1(&head, head);
    delete1(&head, head->next);
    delete2(head->next);
    delete3(head);
    print_list(head);
    
    reverse(&head);
    print_list(head);

    printf("middle node: [%d]\r\n", middle(head)->data);
    printf("last %d-th node: [%d]\r\n", 3, last_kth(head, 3)->data);
    printf("circle is %s existed\r\n", is_circle(head)? "":"not");

    append(&head1, creat_node(2));
    append(&head1, creat_node(5));
    append(&head1, creat_node(8));
    append(&head1, creat_node(10));

    append(&head2, creat_node(3));
    append(&head2, creat_node(4));
    append(&head2, creat_node(7));
    append(&head2, creat_node(12));

    head1 = merge(head1, head2);
    print_list(head1);

    return 0;
}