#include <stdio.h>

int sum(int a, int b, int c)
{
	int x = a + 2;
	int y = b + 1;
	int i = 0;
	while (i < a)
	{
		if (i == a)
		{
			x = a*a;
			if (i == c)
			{
				y = a*c;
				break;
			}
			else
			{
				y = a*b;
			}
		}
		else
		{
			x = b*b;
		}
		i++;
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