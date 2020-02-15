#ifndef _STACK_ARRAY_H_
#define _STACK_ARRAY_H_

template <typename T>
class stack_array
{
private:
    T *array;
    int size;
    int count;
public:
    stack_array(int);
    ~stack_array();
    void push(const T&);
    T peek();
    T pop();
    bool is_empty();
};

#endif