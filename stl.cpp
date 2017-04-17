/*
extern dlink* dlink_init(void* pval);
extern dlink_destoty(dlink* list);
extern void* dlink_get_first(dlink* list);
extern void* dlink_get_last(dlink* list);
extern dlink_insert_first(dlink* list, void* pval);
extern dlink_insert_last(dlink* list, void* pval);
extern dlink_delete_first(dlink* list);
extern dlink_delete_last(dlink* list);
*/

#include <stdio.h>
#include <malloc.h>

typedef struct list_node {
	void *pval;
	struct list_node *prev;
	struct list_node *next;
}node;

typedef struct double_list {
	node *head;
	node* last;
}dlink;

static dlink* dlink_init(void* pval)
{
	node *head = NULL;
	dlink *list = NULL;
	head = (node *)malloc(sizeof(node));
	list = (dlink *)malloc(sizeof(dlink));
	head->prev = head;
	head->next = head;
	head->pval = pval;
	list->head = head;
	list->last = head;
	return list;
}

static void dlink_destory(dlink* list)
{
	node* node = list->head;
	while (node && node->next != list->head)
	{
		node = node->next;
		free(node->prev);
	}
	if (node)
	{
		free(node);
	}
	free(list);
}

static void* dlink_get_first(dlink* list)
{
	return list->head->pval;
}

static void* dlink_get_last(dlink *list)
{
	return list->last->pval;
}

static void dlink_insert_first(dlink* list, void* pval)
{
	node* head = (node *)malloc(sizeof(node));
	head->next = list->head;
	list->head->prev = head;
	list->last->next = head;
	head->prev = list->last;
	head->pval = pval;
	list->head = head;
}

static void dlink_insert_last(dlink *list, void* pval)
{
	node* last = (node *)malloc(sizeof(node));
	list->last->next = last;
	last->prev = list->last;
	last->next = list->head;
	list->head->prev = last;
	last->pval = pval;
	list->last = last;
}

static void dlink_delete_first(dlink* list)
{
	node* head = list->head->next;
	if (head->next == head)
	{
		free(head);
		list->head = list->last = NULL;
		return;
	}
	list->last->next = head;
	head->prev = list->last;
	free(list->head);
	list->head = head;
}

static void dlink_delete_last(dlink* list)
{
	node* last = list->last->prev;
	if (last->next == last)
	{
		free(last);
		list->head = list->last = NULL;
		return;
	}
	last->next = list->head;
	list->head->prev = last;
	free(list->last);
	list->last = last;
}


/*
 * stack
 * extern stack* stack_init(void* pval);
 * extern void* stack_pop(struct stack* stack);
 * extern void* stack_peek(struct stack* stack);
 * extern void stack_push(void* pval, stack* stack);
 */

struct stack {
	dlink *list;
};

static struct stack* stack_init(void* pval)
{
	stack* stack = (struct stack*)malloc(sizeof(stack));
	stack->list = dlink_init(pval);
	return stack;
}

static void* stack_peek(stack* stack)
{
	return dlink_get_first(stack->list);
}

static void* stack_pop(stack* stack)
{
	void* top = dlink_get_first(stack->list);
	dlink_delete_first(stack->list);
	return top;
}

static void stack_push(void* pval, stack* stack)
{
	dlink_insert_first(stack->list, pval);
}

static void stack_destory(stack* stack)
{
	dlink_destory(stack->list);
	free(stack);
}

