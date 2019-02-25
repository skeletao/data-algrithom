/*************************************************************************
    > File Name: fibo.c
    > Author: zxt
    > Mail: zxt@163.com 
    > Created Time: Monday, February 25, 2019 AM08:36:35 HKT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

unsigned long fib(int n)
{
	unsigned long res = 0;
	int i = 1;
	int pre_pre = 0;
	int pre = 1;
	
	if (n < 2)
	{
		return n;
	}

	while (i < n)
	{
		res = pre_pre + pre;
		pre_pre = pre;
		pre = res;
		i++;
	}

	return res;
}

int main(int argc, char *argv[])
{
	printf("fib with %d is %lu\n", 50, fib(50));
}
