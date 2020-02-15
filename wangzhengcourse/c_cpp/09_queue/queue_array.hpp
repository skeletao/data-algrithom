#ifndef _QUEUE_ARRAY_H
#define _QUEUE_ARRAY_H

/*
 * Circular queue
 * 1. based on array
 * 2. return false if enqueue when it is full
 * 3. return null if dequeue when it is empty
 */

template <typename T>
class queue_array
{
private:
    int size;
    int head; // next read position
    int tail; // next write position
    T *array;
public:
    queue_array(int);
    ~queue_array();
    bool enqueue(const T&);
    T dequeue();
    bool is_empty();
    bool is_full();
    int len();
};

#endif
