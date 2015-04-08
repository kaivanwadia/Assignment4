#include <stdio.h>

// 3 dead codes
int func(int a, int b)
{
	int q = a * b;
	int w = b * q; // dead
	for (int i = 0; i < 5; i++)
	{
		w += q * i; // dead
	}

	int b = w * q; // dead

	return q;
}

int main()
{
	int x = func(12, 15);
	printf("%d\n", x);
	return 0;
}