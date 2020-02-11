/*
 *  a sorted array with dynamic used size
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct array {
    int size;
    int used;
    int *p;
};


void dump(struct array *array)
{
    int i = 0;

    for (i = 0; i < array->used; i++)
    {
        printf("array[%d]: %d\r\n", i, array->p[i]);
    }
}

void alloc(struct array *array)
{
    array->p = (int *)malloc(sizeof(int)*array->size);
    assert(array->p != NULL);
}

int insert(struct array *array, int val)
{
    int i = 0;
    if (array->used >= array->size) return -1;
    for (i = 0; i < array->used; i++)
    {
        if (array->p[i] > val) break;
    }
    if (i < array->used)
    {
        memmove(array->p+i+1, array->p+i, sizeof(int)*(array->used-i));
    }
    array->p[i] = val;
    array->used++;
    return 0;
}


int delete2(struct array *array, int idx)
{
    if (idx < 0 || idx >= array->used) return -1;
    memmove(array->p+idx, array->p+idx+1, sizeof(int)*(array->used-idx-1));
    array->used--;
    return 0;
}

int search(struct array *array, int val)
{
    int i = 0;
    for (i = 0; i < array->used; i++)
    {
        if (array->p[i] == val) return i;
    }
    return -1;
}


int main(void)
{
    int i;
    int idx;

    struct array a5 = {5, 0 , NULL};

    alloc(&a5);

    insert(&a5, 5);
    insert(&a5, 7);
    insert(&a5, 2);
    insert(&a5, 1);
    insert(&a5, 8);

    dump(&a5);

    i = 7;
    idx = search(&a5, i);
    printf("array[%d]: %d\r\n", idx, i);

    delete2(&a5, 3);
    dump(&a5);

    return 0;
}