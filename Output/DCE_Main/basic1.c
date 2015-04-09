#include <stdio.h>

int temp(int e)
{
	int df = e * 5;
	return df;
}

int temp1(int e)
{
	int df = e + 5;
	return df;
}

void temp2(int f)
{
	int df = f /2;
	return;
}

int sum(int a, int b)
{
	int i;
	int res = 1*b;
	int c[5] = {1,2,3,4,5};
	int (*foo)(int);
	if (b == 4)
	{
		foo = &temp;
	}
	else
	{
		foo = &temp1;
	}
	for (i = a; i < b; i++)
		c[i] *= i;
	int y =temp(b);
	int x = foo(res);
	temp2(y);
	c[2] = x + y;
	return c[2];
}

int main()
{
	int x = sum(1,2);
	printf("%d\n", x);
	x = temp(3);
	printf("%d\n", x);
	x = temp1(6);
	printf("%d\n", x);
	temp2(9);
	printf("%d\n", x);
	return 1;
}