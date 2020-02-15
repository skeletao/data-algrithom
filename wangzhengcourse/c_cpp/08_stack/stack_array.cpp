#include <iostream>
#include <stdexcept>
#include "stack_array.hpp"


using namespace std;

template <typename T>
stack_array<T>::stack_array(int n)
{
    size = n;
    count = 0;

    array = new T[size];
    if (!array) 
    {
        throw invalid_argument("New array memory failed");
    } 
}

template <typename T>
stack_array<T>::~stack_array()
{
    size = 0;
    count = 0;
    delete[] array;
    array = NULL;
}

template <typename T>
void stack_array<T>::push(const T& data)
{
    if (count == size)
    {
        T* tmp = new T[size*2];
        if (!tmp) throw invalid_argument("Extend array memory failed");
        memcpy(tmp, array, sizeof(T)*size);
        size = size*2;
        delete[] array;
        array = tmp;
    }
    array[count] = data;
    count++;
}

template <typename T>
T stack_array<T>::peek()
{
    if (count == 0) 
    {
        return NULL;
    } else
    {
        return array[count-1];
    }
}

template <typename T>
T stack_array<T>::pop()
{
    if (count == 0)
    {
        return NULL;
    } else
    {
        count--;
        return array[count];
    }
    
}

template <typename T>
bool stack_array<T>::is_empty()
{
    return count? false:true;
}

template <typename T>
void pop_all(stack_array<T> &s)
{
    while (!s.is_empty())
    {
        cout << s.pop() << " ";
    }
    cout << endl;
}

int main(void)
{
    stack_array<int> s(5);
    s.push(5);
    s.push(7);
    s.push(2);
    s.push(1);
    s.push(8);
    s.push(9);
    s.push(9);
    cout << "peek: " << s.peek() << endl;
    pop_all(s);    
    return 0;
}