#include <stdio.h>

int sum(int a, int b, int c)
{
	int x = c * 2;//14
	int y = c + 1;//8
	int i = 0;
	while(i < a)
	{
		y = a*c;
		int j = 0;
		while(j< b)
		{
			x = b*3;
			j++;
		}
		i++;
	}
	return x * y;
}

int main()
{
	int x = sum(0, 0, 7);
	printf("Both loop not run : %d\n", x);
	x = sum(2, 0, 7);
	printf("Outer Loop run : %d\n", x);
	x = sum(2, 5, 7);
	printf("Both loop run : %d\n", x);
	return 0;
}