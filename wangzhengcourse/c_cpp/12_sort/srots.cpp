#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void merge_sentry(int a[], int left, int right, int middle)
{
    int i = 0;
    int j = 0;
    int k = left;
    int left_size = middle-left+1;
    int right_size = right-middle+1;
    int *pleft = (int *)malloc((left_size+1)*sizeof(int));
    int *pright = (int *)malloc((right_size+1)*sizeof(int));
    assert(pleft != NULL && pright != NULL);

    memcpy(pleft, a+left, left_size*sizeof(int));
    memcpy(pright, a+middle+1, right_size*sizeof(int));
    pleft[left_size] = INT_MAX;
    pright[right_size] = INT_MAX;

    while (k <= right)
    {
        if (pleft[i] <= pright[j])
        {
            a[k++] = pleft[i++];
        }
        else
        {
            a[k++] = pright[j++];
        }
    }

    free(pleft);
    free(pright);
}

void merge(int a[], int left, int right, int middle)
{
    int *tmp = (int *)malloc((right-left+1)*sizeof(int));
    assert(tmp != NULL);
    int i = left, j = middle+1, k = 0; 

    while (i <= middle && j <= right)
    {
        if (a[i] <= a[j])
        {
            tmp[k++] = a[i++];

        }
        else
        {
            tmp[k++] = a[j++];
        }
        
    }

    if (i > middle)
    {
        while ( j <= right)
        {
            tmp[k++] = a[j++];
        }
    } else
    {
        while (i <= middle)
        {
            tmp[k++] = a[i++];
        }
    }
    
    memcpy(a+left, tmp, sizeof(int)*(right-left+1));

    free(tmp);
}

void merge_sort_btw(int a[], int left, int right)
{
    int m = 0;

    if (left >= right) return;

    m = (left + right)/2;

    merge_sort_btw(a, left, m);
    merge_sort_btw(a, m+1, right);

    // merge(a, left, right, m);
    merge_sentry(a, left, right, m);
}

void merge_sort(int a[], int n)
{
    merge_sort_btw(a, 0, n-1);
}

// may have bug
int partition2(int a[], int left, int right)
{
    int i = left;
    int j = right;
    int tmp = 0;
    int pivot = a[left];


    while (1)
    {
        while (a[i] <= pivot && i < j) i++;
        while (a[j] > pivot ) j--;
        if (i < j)
        {
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
        else
        {
            break;
        }
    }

    a[left] = a[j];
    a[j] = pivot;
    return j;
}


int partition(int a[], int left, int right)
{
    int i = left;
    int j = left;
    int tmp = 0;

    for (; j < right; j++)
    {
        if (a[j] < a[right])
        {
            if (i != j)
            {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
            i++;
        }
    }


    tmp = a[i];
    a[i] = a[right];
    a[right] = tmp;

    return i;
}

void quick_sort_btw(int a[], int left, int right)
{
    int m = 0;
    if (left >= right) return;

    m = partition(a, left, right);

    quick_sort_btw(a, left, m-1);
    quick_sort_btw(a, m+1, right);
}


void quick_sort(int a[], int n)
{
    quick_sort_btw(a, 0, n-1);
}

int main(void)
{
    int arr[] = {3, 1, 3, 8, 4, 7, 1, 10, 2, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    quick_sort(arr, n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\r\n");
}