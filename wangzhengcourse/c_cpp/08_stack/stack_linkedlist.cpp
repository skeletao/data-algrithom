#include <iostream>
#include <stdexcept>
#include "stack_linkedlist.hpp"

using namespace std;

template <typename T>
stack_linkedlist<T>::stack_linkedlist()
{
    count = 0;
    head = NULL;
}

template <typename T>
stack_linkedlist<T>::~stack_linkedlist()
{
    while (head)
    {
        struct node *tmp = head;
        head = head->next;
        delete tmp;
    }
    count = 0;
}

template <typename T>
void stack_linkedlist<T>::push(const T &data)
{
    struct node* tmp = new node;
    if (!tmp)
    {
        throw invalid_argument("New node memory failed");
    }
    tmp->data = data;
    tmp->next = head;
    head = tmp;
    count++;
}

template <typename T>
T stack_linkedlist<T>::peek()
{
    if (count > 0)
    {
        return head->data;
    } else
    {
        return NULL;
    }
}

template <typename T>
T stack_linkedlist<T>::pop()
{
    if (count > 0)
    {
        struct node *tmp = head;
        T val = head->data;
        head = head->next;
        delete tmp;
        count--;
        return val;
    } else
    {
        return NULL;
    }
}

template <typename T>
bool stack_linkedlist<T>::is_empty()
{
    return count? false:true;
}

template <typename T>
void pop_all(stack_linkedlist<T> &s)
{
    while (!s.is_empty())
    {
        cout << s.pop() << " ";
    }
    cout << endl;
}


int main(void)
{
    stack_linkedlist<string> s;
    s.push("girl");
    s.push("smart");
    s.push("a");
    s.push("is");
    s.push("wobu");

    cout << "peek: " << s.peek() << endl;
    pop_all(s);

    s.push("girl");
    s.push("smart");
    s.push("a");
    s.push("is");
    s.push("wobu");
    pop_all(s);

    return 0;
}