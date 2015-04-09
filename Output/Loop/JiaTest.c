#include <stdio.h>
int faint(int x)
{
    int y = x * x;
    int z = x - 3;
    int w = 1;

    for (int i = 0; i < y; ++i)
        w = w + i;

    y--;

    return z;
}

int main()
{
	int x = faint(12);
	printf("%d\n", x);
	return 0;
}
