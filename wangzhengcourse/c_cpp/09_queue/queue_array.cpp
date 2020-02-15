#include <iostream>
#include <stdexcept>
#include "queue_array.hpp"

using namespace std;


template <typename T>
queue_array<T>::queue_array(int n)
{
    size = n;
    head = 0;
    tail = 0;
    array = new T[size];
    if (!array) throw invalid_argument("New array memory failed");
}

template <typename T>
queue_array<T>::~queue_array()
{
    size = 0;
    head = 0;
    tail = 0;
    delete[] array;
    array = NULL;
}

template <typename T>
bool queue_array<T>::enqueue(const T& data)
{
    if ((tail+1)%size == head) return false;
    array[tail] = data;
    tail = (tail+1)%size;
    return true;
}

template <typename T>
T queue_array<T>::dequeue()
{
    if (head == tail) return NULL;
    T tmp = array[head];
    head = (head+1)%size;
    return tmp;
}

template <typename T>
bool queue_array<T>::is_empty()
{
    return (head == tail)? true:false;
}

template <typename T>
bool queue_array<T>::is_full()
{
    return ((tail+1)%size == head)? true:false;
}

template <typename T>
int queue_array<T>::len()
{
    return (tail+size-head)%size;
}

template <typename T>
void dequeue_all(queue_array<T>& q)
{
    while (!q.is_empty())
    {
        cout << q.dequeue() << " ";
    }
    cout << endl;
}

int main(void)
{
    queue_array<int> q(5);

    q.enqueue(5);
    q.enqueue(4);
    q.enqueue(3);
    q.enqueue(2);
    q.enqueue(1);

    cout << "length: " << q.len() << endl;
    dequeue_all(q);

    return 0;
}




