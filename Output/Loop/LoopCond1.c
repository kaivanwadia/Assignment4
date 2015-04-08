#include <stdio.h>

int sum(int a, int b, int c)
{
	int x = a * 2;
	int y = b + 1;
	for (int i = 0; i < a; i++)
	{
		if (x > c)
		{
			x = b+3;
		}
		else
		{
			y = a + 2;
		}
	}
	return x * y;
}

int main()
{
	int x = sum(0, 0, 0);
	printf("Loop not run : %d\n", x);
	x = sum(10, 1, 10);
	printf("Loop run : %d\n", x);
	x = sum(10, 2, 0);
	printf("Loop run : %d\n", x);
	x = sum(10, 3, 100);
	printf("Loop run : %d\n", x);
	return 0;
}