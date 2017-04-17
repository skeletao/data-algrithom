#include <iostream>
using namespace std;

static void bsort(int *array, int n)
{
	int k = n;
	int i = 0, j = 0, temp = 0, index = 0;
	while (k > 1)
	{
		for (j = 1; j < k; j++)
		{
			if (array[j - 1] > array[j])
			{
				temp = array[j - 1];
				array[j - 1] = array[j];
				array[j] = temp;
				index = j;
			}
		}
		k = index;
		index = 0;
	}
}


static void isort1(int *array, int n)
{
	int i = 0, j = 0, k = 0, temp = 0;
	for (i = 1; i < n; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (array[i] <= array[j])
			{
				break;
			}
		}
		if (j != i - 1)
		{
			temp = array[i];
			for (k = i; k > j; k--)
			{
				array[k] = array[k - 1];

			}
			array[j] = temp;
		}
	}
}

static void isort2(int *array, int n)
{
	int i = 0, j = 0, k = 0, temp = 0;
	for (i = 1; i < n; i++)
	{
		temp = array[i];
		for (j = i - 1; j >= 0 && temp < array[j]; j--)
		{
			array[j + 1] = array[j];
		}
		array[j + 1] = temp;
	}
}


static void isort3(int *array, int n)
{
	int i = 0, j = 0, k = 0, temp = 0;
	for (i = 1; i < n; i++)
	{
		for (j = i - 1; j >= 0 && array[j + 1] < array[j]; j--)
		{
			temp = array[j + 1];
			array[j + 1] = array[j];
			array[j] = temp;
		}
	}
}

static void qsort(int *array, int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, val = 0;
		val = array[i];
		while (i < j)
		{
			while (array[j] > val && i < j)
			{
				j--;
			}
			if (i < j)
			{
				array[i++] = array[j];
			}
			while (array[i] < val && i < j)
			{
				i++;
			}
			if (i < j)
			{
				array[j--] = array[i];
			}
		}
		array[i] = val;
		qsort(array, l, i - 1);
		qsort(array, i + 1, r);
	}
}

static void msort(int* array, int n)
{
	int i = 0, mid = n / 2, j = mid;
	int* temp = (int *)malloc(sizeof(int)*n);
	if (n > 1)
	{
		msort(array, mid);
		msort(array + mid, n - mid);
		while (i < mid && j < n)
		{
			if (array[i] < array[j])
			{
				*temp++ = array[i];
				i++;
			}
			else
			{
				*temp++ = array[j];
				j++;
			}
		}
		while (i < mid)
		{
			*temp++ = array[i++];
		}
		while (j < n)
		{
			*temp++ = array[j++];
		}
		temp -= n;
		for (i = 0; i < n; i++)
		{
			array[i] = temp[i];
		}
		free(temp);
		temp = NULL;
	}
	else
	{
		free(temp);
		temp = NULL;
	}
}

static void heapModify(int* array, int index, int size)
{
	int temp = array[index], j = 2 * index + 1;
	while (j < size)
	{
		if (j + 1 < size && array[j] > array[j + 1])
		{
			j++;
		}
		if (temp <= array[j])
		{
			break;
		}
		array[index] = array[j];
		j = 2 * index + 1;
		index = j;
	}
	array[index] = temp;
}

static void hsort(int* array, int size)
{
	int i = 0, j = 0, temp = 0;
	for (i = size / 2 - 1; i > -1; i--)
	{
		heapModify(array, i, size);
	}
	while (size > 1)
	{
		temp = array[size - 1];
		array[size - 1] = array[0];
		array[0] = temp;
		size--;
		heapModify(array, 0, size);
	}
}
