#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* 求解平方根， 要求精度 1e-6 */
#define E 6 //精确到小数点6位
double binary_search_sqrt(double num)
{
    int digits = E + 1;
    int i = 0;
    int low = 0;
    int hi = 0.0;
    int mid = 0.0;
    double step = 0.0;
    double res = 0.0;
    double tmp = 0.0;

    for (; i < digits; i++)
    {
        step = pow(10, -i);
        low = 0;
        hi = (i == 0) ? num: 9;
        while (low <= hi)
        {
            mid = low + (hi - low)/2;
            tmp = (i == 0) ? mid: mid*step + res;

            if (tmp*tmp < num) 
            {
                if (mid == ((i == 0) ? num:  9) || (tmp+step)*(tmp+step) > num) 
                {
                    res = tmp;
                    break;
                }
                low = mid + 1;
            } else
            {
                hi = mid - 1;
            }
        }
    }
    return res;
}

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

int binary_search_first_equal(int a[], int n, int val)
{
    int low = 0;
    int hi = n-1;
    int mid = 0;

    while (low <= hi)
    {
        mid = low + ((hi - low)>>1);
        if (val <= a[mid])
        {
            if (val == a[mid])
            {
                if (mid == 0 || a[mid-1] != val) return mid;
            }
            hi = mid - 1;
        } else
        {
            low = mid + 1;
        }
    }
    return -1;
}

int binary_search_last_equal(int a[], int n, int val)
{
    int low = 0;
    int hi = n - 1;
    int mid = 0;

    while (low <= hi)
    {
        mid = low + ((hi - low)>>1);
        if (val >= a[mid])
        {
            if (val == a[mid])
            {
                if (mid == n-1 || a[mid+1] != val) return mid;
            }
            low = mid + 1;
        } else 
        {
            hi = mid - 1;
        }
    }
    return -1;
}


int binary_search_first_not_less(int a[], int n, int val)
{
    int low = 0;
    int hi = n - 1;
    int mid = 0;

    while (low <= hi)
    {
        mid = low + ((hi - low)>>1);
        if (val <= a[mid])
        {
            if (mid == 0 || val > a[mid - 1]) return mid;
            hi = mid - 1;
        } else
        {
            low = mid + 1;
        }
    }
    return -1;
}


int binary_search_last_not_greater(int a[], int n, int val)
{
    int low = 0;
    int hi = n - 1;
    int mid = 0;

    while (low <= hi)
    {
        mid = low + ((hi - low)>>1);
        if (val >= a[mid]) 
        {
            if (mid == n - 1 || val < a[mid + 1]) return mid;
            low = mid + 1;
        } else
        {
            hi = mid - 1;
        }
    }
    return -1;
}

int main(void)
{
    int arr[] = {1, 3, 3, 5, 5, 5, 6,8,9,10,11,23,42,53,99,123};
    int data = 0;
    int res = 0;

    double num = 31;
    double f = 0.0;

    int n = sizeof(arr)/sizeof(int);

    data = 7;
    res = binary_search_last_not_greater(arr, n, data);
    printf("data [%d] is %s in array, index is [%d]\r\n", data, (res < 0) ? "not":"", res);

    data = 5;
    res = binary_search_last_not_greater(arr, n, data);
    printf("data [%d] is %s in array, index is [%d]\r\n", data, (res < 0) ? "not":"", res);

    f = binary_search_sqrt(num);
    printf("sqrt of [%f] is [%f]\r\n", num, f);
}