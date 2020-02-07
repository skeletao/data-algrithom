#include <stdlib.h>
#include <stdio.h>

int binary_search(int a[], int n, int val)
{
    int low = 0;
    int hi = n-1;
    int mid = 0;

    while (low <= hi)
    {
        mid = low + ((hi - low)>>1);
        if (val == a[mid])
        {
            return mid;
        } else if (val < a[mid])
        {
            hi = mid-1;
        } else
        {
            low = mid+1;
        }
    }
    return -1;
}

int main(void)
{
    int arr[] = {1, 3, 5,6,8,9,10,11,23,42,53,99,123};
    int data = 0;
    int res = 0;

    int n = sizeof(arr)/sizeof(int);

    data = 0;
    res = binary_search(arr, n, data);
    printf("data [%d] is %s in array, index is [%d]\r\n", data, (res < 0) ? "not":"", res);

    data = 23;
    res = binary_search(arr, n, data);
    printf("data [%d] is %s in array, index is [%d]\r\n", data, (res < 0) ? "not":"", res);
}