#include <stdio.h>

int sum(int a, int b, int c)
{
	int x = a + 2;
	int y = b + 1;
	for (int i = 0; i < a; i++)
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
				for (int j = 0; j < b; j++)
				{
					y = y*2;
					if ( y == c)
					{
						break;
					}
				}
			}
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