/*************************************************************************
    > File Name: qsort.c
    > Author: zxt
    > Mail: zxt@163.com 
    > Created Time: Monday, February 25, 2019 PM01:13:53 HKT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX_THRES 3
#define STACK_SIZE 8*sizeof(unsigned int)
#define STACK_PUSH(low, high) ((top->lo = low), (top->hi = high), top++)
#define STACK_POP(low, high)  (top--, (low = top->lo), (high = top->hi))

typedef struct stack_node_t {
	int lo;
	int hi;
}stack_node;

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


void insert_sort(int a[], n)
{
	int i = 1, j = 0, tmp = 0;

	for (i = 1; i < n; i++)
	{
		tmp = a[i];

		for(j = i; j > 0 && a[j-1] > a[i]; j--)
		{
			a[j] = a[j-1];
		}
		a[j] = tmp;
	}
}

int partition(int a[], int left, int right)
{

	int center  = (left + right)/2;
	
	if (a[left] > a[center])
	{
		swap(&a[left], &a[center]);
	}
	if (a[left] > a[right])
	{
		swap(&a[left], &a[right]);
	}
	if (a[center] > a[right])
	{
		swap(&a[center], &a[right]);
	}
	swap(&a[center], &a[right-1]);

	pivot = a[right-1];
	i = left;
	j = right - 1;

	for(;;)
	{
		while (a[++i] < pivot)
		{
		}
		while (a[--j] > pivot)
		{
		}
		if (i < j)
		{
			swap(&a[i], &a[j]);
		}
		else
		{
			break;
		}
	}	
	swap(&a[right-1],&a[i]);
	return i;
}


void quick_sort(int a[], int left, int right)
{
	int i = 0;
	int n = right - left + 1;
	if (n < MAX_THRES)
	{
		insert_sort(a+left, n);
	}
	
	i = partition(a, left, right);

	quick_sort(a, left, i-1);
	quick_sort(a, i+1, right);
}



void quick_sort(int a[], int left, int right)
{
	int mid = 0;
	int lo = left, hi = right;
	register int *arr = a;
	if (right-left+1 > MAX_THRES)
	{
		stack_node stack[STACK_SIZE] = {{0}};
	    stack_node *top = stack;
		STACK_PUSH(0, 0);
		
		while (stack < top)
		{
			mid = partition(arr, lo, hi);

			if (mid-1-low <= MAX_THRES)
			{
				if (hi-mid-1 <= MAX_THRES)
				{
					STACK_POP(lo, hi);
				}
				else
				{
					lo = mid+1;
				}
			}
			else
			{
				hi  = mid -1;
			}
		}
	} 
	insert_sort(arr+left, right-left+1);
}


