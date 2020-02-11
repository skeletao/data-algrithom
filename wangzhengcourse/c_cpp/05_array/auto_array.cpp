#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "array.hpp"


array* create_array(void)
{
    array *a = NULL;
    a = (array *)malloc(sizeof(array));
    if (a == NULL) return NULL;
    a->size = 0;
    a->type = 0;
    a->len = 0;
    a->cpy = NULL;
    a->free = NULL;
    a->cmp = NULL;
    a->data = NULL;
}

void init_array(array *a, size_t size, size_t type)
{
    if (a && (size > 0) && (type > 0))
    {
        a->data = calloc(size, type);
        assert(a->data != NULL);
        a->size = size;
        a->type = type;
    }
}

int insert_array(array *a, size_t pos, const void *value)
{
    int i = 0;
    if (a == NULL || value == NULL || (pos <= 0) || (pos > a->size)) return -1;

    for (int i = a->len; i > pos-1; i--)
    {
        if (a->cpy) 
        {
            a->cpy(a->data+i*a->type, a->data+(i-1)*a->type);
        } else
        {
            memcpy(a->data+i*a->type, a->data+(i-1)*a->type, a->type);
        }
    }

    if (a->cpy) 
    {
        a->cpy(a->data+(pos-1)*a->type, value);
    } else
    {
        memcpy(a->data+(pos-1)*a->type, value, a->type);
    }    
    a->len++;
    return 0;
}

size_t search_array(array *a, const void *value)
{
    int i = 0;
    int res = 0;
    if (a == NULL || value == NULL) return -1;
    for (i = 0; i < a->len; i++)
    {
        if (a->cmp)
        {
            res = a->cmp(a->data+i*a->type, value);
        } else
        {
            res = memcmp(a->data+i*a->type, value, a->type);
        }
        if (res == 0) return i;
    }
    return -1;
}

int modify_array(array *a, size_t pos, const void *value)
{
    if (a == NULL || value == NULL || pos <= 0 || pos > a->len) return -1;

    if (a->cpy) 
    {
        a->cpy(a->data+(pos-1)*a->type, value);
    } else
    {
        memcpy(a->data+(pos-1)*a->type, value, a->type);
    }   

    return 0;
}

int delete_array_pos(array *a, size_t pos)
{
    int i = 0;
    if (a == NULL || pos <= 0 || pos > a->len) return -1;
    
    for (i = pos; i <= a->len; i++)
    {
        if (a->cpy)
        {
            a->cpy(a->data+(i-1)*a->type, a->data+i*a->type);
        } else
        {
            memcpy(a->data+(i-1)*a->type, a->data+i*a->type, a->type);
        }
    }
    a->len--;
    return 0;
}

int delete_array_value(array *a, const void *value)
{
    int idx = 0;
    idx = search_array(a, value);
    if (idx >= 0)
    {
        delete_array_pos(a, idx+1);
    }
}


void free_array(array *a)
{
    if (a == NULL) return;
    if (a->free) 
    {
        a->free(a->data);
    } else
    {
        free(a->data);
    }
    free(a);
    a = NULL;
}


int main(void)
{
    int idx = 0;
    int val = 0;
    int res = 0;
    int i = 0;
    int nums[] = {5, 7, 2, 1, 8};

    array *a = create_array();
    init_array(a, 5, 1);

    for (i = 1; i <= 5; i++)
    {
        insert_array(a, i, &nums[i-1]);
    }

    val = 7;
    idx = search_array(a, &val);

    val = 3;
    modify_array(a, 3, &val);

    delete_array_pos(a, 3);

    val = 7;
    delete_array_value(a, &val);

    free_array(a);
}