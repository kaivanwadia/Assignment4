#include <stdio.h>

int sum(int a, int b, int c)
{
	int x = a * 2;
	int y = c + b;
	for (int i = 0; i < a; i++)
	{
		if (i == a)
		{
			x = a*a;
			break;
		}
		else
		{
			x = b*b;
		}
	}
	return x * y;
}

int main()
{
	int x = sum(2, 0, 3);
	printf("Both loop not run : %d\n", x);
	x = sum(6, 3, 5);
	printf("Outer Loop run : %d\n", x);
	x = sum(3, 5, 9);
	printf("Both loop run : %d\n", x);
	return 0;
}