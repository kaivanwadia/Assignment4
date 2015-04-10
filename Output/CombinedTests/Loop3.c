#include <stdio.h>

int sum(int a, int b, int c)
{
	int x = a*2;
	int y = c + 2;
	for (int i = 0; i < b; i++)
	{
		x = a+b;
		y = x*c;
		for (int j = 0; j < c; j++)
		{
			y= y*2;
		}
	}
	int ret = a*x;
	return x;
}

int main()
{
	int x = sum(2, 0, 3);
	printf("Loop not run : %d\n", x);
	x = sum(2, 5, 5);
	printf("Loop run : %d\n", x);
	x = sum(2, 5, 0);
	printf("Loop run : %d\n", x);
	return 0;
}