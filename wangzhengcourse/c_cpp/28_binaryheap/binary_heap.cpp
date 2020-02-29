#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include <iostream>

#define compare(x, y, dir)  (((x < y) ^ (dir == 0)) ? true : false) // x: parent node; y: child node

class Binary_heap
{
private:
    int capcity;
    int cnt;
    int dir; // 0: max heap; 1: min heap
    int *array;
    bool flag; // new memory
    void swap(int, int);
    void heapify(int, int);
public:
    Binary_heap(int, int);
    Binary_heap(int *, int, int);
    ~Binary_heap();
    void build_heap();
    void insert(int);
    void remove(int);
    void sort();
    void display();
};

Binary_heap::Binary_heap(int size, int direction=0)
{
    capcity = size;
    dir = direction;
    array = new int[capcity];
    flag = true;
    cnt = 0;
}

Binary_heap::Binary_heap(int *a, int n, int direction=0)
{
    array = a;
    cnt = n;
    capcity = n;
    dir = direction;
    flag = false;
    build_heap();
}

Binary_heap::~Binary_heap()
{
    if (flag) delete[] array;
    array = nullptr;
}

void Binary_heap::swap(int i, int j)
{
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void Binary_heap::heapify(int i, int cnt)
{
    int max = i;

    while (true)
    {
        if (2*i+1 < cnt && compare(array[2*i+1], array[i], dir)) max = 2*i+1;
        if (2*i+2 < cnt && compare(array[2*i+2], array[2*i+1], dir)) max = 2*i+2;
        if (i == max) break;
        swap(i, max);
        i = max;
    }
}

void Binary_heap::build_heap()
{
    for (int i = (cnt-2)/2; i >= 0; i--)
    {
        heapify(i, cnt);
    }   
}

void Binary_heap::insert(int value)
{
    
    if (cnt == capcity) return;

    int i = cnt;
    array[cnt++] = value;

    while (true)
    {
        if ( i > 0 && compare(array[i], array[(i-1)/2], dir)) 
        {
            swap(i, (i-1)/2);
            i = (i-1)/2;
        }
        else
        {
            break;
        }
    }
}

void Binary_heap::remove(int i)
{
    if (i >= cnt) return;

    array[i] = array[cnt-1];
    cnt--;

    heapify(i, cnt);
}


void Binary_heap::sort()
{
    for (int i = cnt-1; i > 0; i--)
    {
        swap(0, i);
        heapify(0, i);
    }
}


void Binary_heap::display()
{
    for (int i = 0; i < cnt; i++)
    {
        std::cout << " " << array[i];
    }
    std::cout << std::endl;
}

#endif


int main(void)
{
    int a[] = {7,5,19,8,4,1,20,13,16};
    int n = sizeof(a)/sizeof(a[0]);

    Binary_heap heap = Binary_heap(a, n, 0);
    heap.display();

    heap.remove(1);
    heap.display();

    heap.insert(16);
    heap.display();

    heap.sort();
    heap.display();

    return 0;
}