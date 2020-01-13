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
    if (n < 2) return;

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


int main(void)
{
    int arr[] = {3, 6, 2, 7, 2, 9};
    int n = sizeof(arr)/sizeof(arr[0]);
    insert_sort(arr, n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\r\n");
}