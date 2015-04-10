#include <stdio.h>

int sum(int a, int b)
{
	int x = a * 2;
	int c = a * b;
	for (int i = 0; i < b; i++)
	{
		if (i > 3)
		{
			x = b*3;
		}
	}
	return c * 2;
}

int main()
{
	int x = sum(5, 0);
	printf("Loop not run : %d\n", x);
	x = sum(10, 10);
	printf("Loop run : %d\n", x);
	return 0;
}