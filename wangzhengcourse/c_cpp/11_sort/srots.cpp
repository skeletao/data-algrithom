#include <stdio.h>

void bubble_sort(int a[], int n)
{
    if (n < 2) return;

    for (int i = 0; i < n; i++)
    {
        bool swap_flag = false;

        for (int j = 0; j < n-i-1; j++)
        {
            if (a[j] > a [j+1])
            {
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                swap_flag = true;
            }
        }

        if (!swap_flag) break;
    }

}


void insert_sort(int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int tmp = a[i];
        int j = i - 1;
        while(a[j] > tmp && j >= 0)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = tmp;
    }
}

void select_sort(int a[], int n)
{
    int i, j;
    if (n < 2) return;

    for (i = 0; i < n; i++)
    {
        int index = i;
        for (j = i+1; j < n; j++)
        {
            if (a[index] > a[j])
            {
                index = j;
            }
        }
        if (index != i) 
        {
            int tmp = a[i];
            a[i] = a[index];
            a[index] = tmp;
        }
    }
}

int main(void)
{
    int arr[] = {3, 1, 3, 8, 4, 7, 1, 10, 2, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    select_sort(arr, n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\r\n");
    return 0;
}