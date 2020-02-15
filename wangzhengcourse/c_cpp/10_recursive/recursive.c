#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fib(int n)
{
    if (n == 1 || n == 2) 
    {
        return n;
    }
    else
    {
        return fib(n-1)+fib(n-2);
    }
}

int factorial(int n)
{
    if (n == 0 || n == 1) 
    {
        return n;
    }
    else
    {
        return n*factorial(n-1);
    }
}

void swap(char *s, int m, int n)
{
    char c = s[m];
    s[m] = s[n];
    s[n] = c;
}

void permutate(char *s, int l, int r)
{
    int i = 0;
    if (l == r) 
    {
        printf("%s\r\n", s);
        return;
    }
    for (i = l; i <= r; i++)
    {
        swap(s, l, i);
        permutate(s, l+1, r);
        swap(s, l, i);
    } 
}


int main(void)
{
    char ss[] = "abc";
    permutate(ss, 0, sizeof(ss)-2);

    printf("%d\r\n", factorial(3));

    printf("%d\r\n", fib(5));

    return 0;
}