#ifndef _QUEUE_LINKED_LIST_H
#define _QUEUE_LINKED_LIST_H

template <typename T>
class queue_linkedlist
{
private:
    struct node{
        T data;
        struct node *next;
    };
    int count;
    struct node* head;
    struct node* tail;
public:
    queue_linkedlist();
    ~queue_linkedlist();
    void enqueue(const T&);
    T dequque();
    bool is_empty();
    int len();
};

#endif