#ifndef FIND_K_LARGEST_HPP
#define FIND_K_LARGEST_HPP

#include <iostream>

#define COMPARE(arr, i, j, max) ((((arr[i]) < (arr[j])) ^ max) ? true : false)

class MaxMinHeap
{
private:
    int size;
    int *array;
    bool is_max; // ture: means max heap; false: means min heap
public:
    MaxMinHeap(int *, int, bool);
    ~MaxMinHeap();
    void Swap(int, int);
    void Heapify(int);
    void BuildHeap();
    void Display();
};

MaxMinHeap::MaxMinHeap(int *arr, int n, bool flag=true) 
{
    size = n;
    array = arr;
    is_max = flag;
    BuildHeap();
}

MaxMinHeap::~MaxMinHeap()
{
    array = nullptr;
}

void MaxMinHeap::Swap(int i, int j)
{
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void MaxMinHeap::Heapify(int idx)
{
    int extreme = idx;
    while (1)
    {
        if (idx*2+1 < size && COMPARE(array, idx*2+1, idx, is_max)) extreme = idx*2+1;
        if (idx*2+2 < size && COMPARE(array, idx*2+2, idx*2+1, is_max)) extreme = idx*2+2;
        if (extreme == idx) break;
        Swap(idx, extreme);
        idx = extreme;
    }
}

void MaxMinHeap::BuildHeap()
{
    for (int i = (size-2)/2; i >= 0; i--) Heapify(i);
}

void MaxMinHeap::Display()
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void FindKLargest(int *arr, int n, int k)
{
    MaxMinHeap heap(arr, k, false);
    for (int i = k; i < n; i++)
    {
        if (arr[i] < arr[0]) continue;
        heap.Swap(0, i);
        heap.Heapify(0);
    }
    heap.Display();
}


int main(void)
{
    int a[] = {7,5,19,8,4,1,20,13,16};
    int n = sizeof(a)/sizeof(a[0]);

    FindKLargest(a, n, 3);
    FindKLargest(a, n, 5);

    return 0;
}

#endif