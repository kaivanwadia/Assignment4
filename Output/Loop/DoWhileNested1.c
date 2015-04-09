#include <stdio.h>

int sum(int a, int b, int c)
{
	int x = c*3;
	int y = c*2;
	int i = 0;
	do
	{
		x = x*2;
		int j = 0;
		do
		{
			y = b+2;
			j++;
		}while(j<a);
		i++;
	}while(i<b);
	return x*y;
}

int main()
{
	int x = sum(0, 0, 3);
	printf("Both loop not run : %d\n", x);
	x = sum(2, 0, 3);
	printf("Outer Loop run : %d\n", x);
	x = sum(2, 5, 3);
	printf("Both loop run : %d\n", x);
	return 0;
}