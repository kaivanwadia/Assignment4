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

	if( a < 5)
	{
		q = 10;
		w = 15;
		a = 100 * a; // dead
	}
	else
	{
		a = 5 * b; // dead
		q = w * 5;
		b = 4 + 2 + w; // dead
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