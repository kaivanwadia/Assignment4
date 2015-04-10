#include <stdio.h>

// 0 Dead codes
int func(int a, int b)
{
	int q = a * b;
	int w = b * q;
	for (int i = 0; i < 5; i++)
	{
		w += q * i;
	}

	b = w * q;

	return b;
}

int main()
{
	int x = func(12, 15);
	printf("%d\n", x);
	return 0;
}