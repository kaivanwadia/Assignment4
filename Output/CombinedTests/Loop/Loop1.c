#include <stdio.h>

int sum(int a, int b)
{
	int x = 2;
	for (int i = 0; i < b; i++)
	{
		x = 10;
	}
	return b*x;
}

int main()
{
	int x = sum(2, 0);
	printf("Loop not run : %d\n", x); // Should print 2
	x = sum(2, 5);
	printf("Loop run : %d\n", x); // Should print 10
	return 0;
}