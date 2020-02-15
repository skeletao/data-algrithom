#ifndef _STACK_LINKED_LIST_H
#define _STACK_LINKED_LIST_H

template <typename T>
class stack_linkedlist
{
private:
    struct node 
    {
        T data;
        struct node *next;
    };
    struct node* head;
    int count;
public:
    stack_linkedlist();
    ~stack_linkedlist();
    void push(const T&);
    T pop();
    T peek();
    bool is_empty();
};

#endif