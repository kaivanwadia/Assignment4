#include <stdio.h>

int sum(int x)
{
	// x = x + 1;
	int a = x + 2;
	int b = a - 3;
	int c = a + b;
	return b;
}

int main()
{
	int x = sum(3);
	printf("%d\n", x);
	return 2;
}