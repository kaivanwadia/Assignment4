#include <stdio.h>

int sum(int x, int y)
{
	int a = x*3;
	do
	{
		a = x + 1;
	}while (a < 100);
	return a;
}

int main()
{
	int x = sum(3, 4);
	printf("%d\n", x);
	return 1;
}