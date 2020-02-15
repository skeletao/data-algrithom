#include <iostream>
#include <stdexcept>
#include "queue_linkedlist.hpp"

using namespace std;

template <typename T>
queue_linkedlist<T>::queue_linkedlist()
{
    count = 0;
    head = NULL;
    tail = NULL;
}

template <typename T>
queue_linkedlist<T>::~queue_linkedlist()
{
    while (head)
    {
        struct node *tmp = head;
        head = head->next;
        delete tmp;
    }
    count = 0;
    tail = NULL;
}

template <typename T>
void queue_linkedlist<T>::enqueue(const T &data)
{
    struct node *tmp = new node;
    if (!tmp) throw invalid_argument("New node memory failed");
    tmp->data = data;
    tmp->next = NULL;

    if (count == 0)
    {
        head = tmp;
        tail = tmp;
    } else
    {
        tail->next = tmp;
        tail = tmp;
    }
    
    count++;
}

template <typename T>
T queue_linkedlist<T>::dequque()
{
    if (count > 0)
    {
        struct node *tmp = head;
        T data = tmp->data;
        head = head->next;
        delete tmp;
        count--;
        if (count == 0) tail = NULL;
        return data;
    } else
    {
        return NULL;
    }
}

template <typename T>
bool queue_linkedlist<T>::is_empty()
{
    return count? false:true;
}

template <typename T>
int queue_linkedlist<T>::len()
{
    return count;
}

template <typename T>
void dequeue_all(queue_linkedlist<T> &q)
{
    while (!q.is_empty())
    {
        cout << q.dequque() << " ";
    }
    cout << endl;
}


int main(void)
{
    queue_linkedlist<string> q;

    q.enqueue("wobu");
    q.enqueue("is");
    q.enqueue("a");
    q.enqueue("smart");
    q.enqueue("girl");
    dequeue_all(q);

    q.enqueue("wobu");
    q.enqueue("is");
    q.enqueue("a");
    q.enqueue("smart");
    q.enqueue("girl");
    dequeue_all(q);

    return 0;
}
