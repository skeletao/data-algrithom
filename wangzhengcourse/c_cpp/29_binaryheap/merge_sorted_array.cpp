#ifndef MERGE_SORTED_ARRAY_HPP
#define MERGE_SORTED_ARRAY_HPP

#include <iostream>

#define COMPARE(arr, i, j, max) ((((arr[i]).value < (arr[j]).value) ^ max) ? true : false)

class MaxMinHeap
{
public:
    struct node
    {
        int value;
        int row;
        int column;
    };
private:
    int size;
    node *array;
    bool is_max; // ture: means max heap; false: means min heap
public:
    MaxMinHeap(node *, int, bool);
    ~MaxMinHeap();
    void Swap(int, int);
    void Heapify(int);
    void BuildHeap();
    node *GetTop();
    void Remove_Top();
    void Display();
};

MaxMinHeap::MaxMinHeap(node *arr, int n, bool flag=true) 
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
    node tmp = array[i];
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

MaxMinHeap::node *MaxMinHeap::GetTop()
{
    return array;
}

void MaxMinHeap::Remove_Top()
{
    Swap(0, size-1);
    size -= 1;
    Heapify(0);
}

void MaxMinHeap::Display()
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i].value << " ";
    }
    std::cout << std::endl;
}


int *MergeSortedArray(int *arr, int m, int n, bool is_max)
{
    int *res = new int[m*n];

    MaxMinHeap::node *root = new MaxMinHeap::node[m];

    for (int i = 0; i < m; i ++)
    {
        root[i].value = *(arr+i*n);
        root[i].row = i;
        root[i].column = 0;
    }
    MaxMinHeap heap(root, m, is_max);

    for (int i = 0; i < m*n; i++)
    {
        MaxMinHeap::node *top = heap.GetTop();
        res[i] = top->value;
        std::cout << res[i] << " ";

        if ((top->column+1) < n)
        {
            top->column += 1;
            top->value = *(arr+top->row*n + top->column);
            heap.Heapify(0);
        } 
        else
        {
            heap.Remove_Top();
        }
    }
    std::cout << std::endl;
}

int main(void)
{
    int a[][4] = {{2, 6, 12, 34}, {1, 9, 20, 1000}, {23, 34, 90, 2000}}; 

    int m = sizeof(a)/sizeof(a[0]);
    int n = sizeof(a[0])/sizeof(a[0][0]);

    MergeSortedArray((int *)a, m, n, false);

    return 0;
}





#endif