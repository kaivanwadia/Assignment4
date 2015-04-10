#include <stdio.h>

int sum(int a, int b)
{
	int c = b*2;
	int x = a*2;
	int y = 0;
	for (int i = 0; i < b; i++)
	{
		x = a+b;
		y = x*c;
	}
	int ret = a*x;
	return x;
}

int main()
{
	int x = sum(2, 0);
	printf("Loop not run : %d\n", x); // Should print 8
	x = sum(2, 5);
	printf("Loop run : %d\n", x); // Should print 14
	return 0;
}