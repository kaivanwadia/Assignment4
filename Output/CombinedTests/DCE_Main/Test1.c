#include <stdio.h>

// 4 dead codes
int func(int a, int b)
{
	int x = a * b;
	int y = a + x; // dead
	int z = y + b; // dead 
	int w = y + z; // dead
	w += x; // dead

	return x;
}

int main()
{
	int x = func(12, 15);
	printf("%d\n", x);
	return 0;
}