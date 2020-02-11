#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct array {
    size_t size;
    size_t type;
    size_t len;
    void (*cpy)(void *ptr1, const void *ptr2);
    void (*free)(void *ptr);
    int (*cmp)(const void *ptr1, const void *ptr2);
    void *data;
}array;


#define set_array_cpy(a, m) ((a)->cpy = (m))
#define set_array_free(a, m) ((a)->free = (m))
#define set_array_cmp(a, m) ((a)->cmp = (m))

#define get_array_cpy(a) ((a)->cpy)
#define get_array_free(a) ((a)->free)
#define get_array_cmp(a) ((a)->cmp)


array* create_array(void);
void init_array(array *a, size_t size, size_t type);
int insert_array(array *a, size_t pos, const void *value);
size_t search_array(array *a, const void *value);
int modify_array(array *a, size_t pos, const void *value);
int delete_array_value(array *a, const void *value);
int delete_array_pos(array *a, size_t pos);
void free_array(array *a);

#endif

