#include <stdio.h>

// 0 Dead codes
int func(int a, int b)
{
	int q = a * b;
	int w = b * q;
	for (int i = 0; i < 5; i++)
	{
		w += q * i;
		for(int j = 0; j < b; j++)
		{
			if(w < 22)
			{
				a = 15 * b; // dead
				w += 1;
				q -= 1;
				b *= 11;
			}
			else
			{
				b *= -1;
			}
		}
		w -= b;
	}

	if( a < 5)
	{
		q = 10;
		w = 15;
		a = 100; // dead
	}
	else
	{
		a = 5; // dead
		q = w * 5;
		b = 4 + 2 + w + a; // dead
	}

	b = w * q;

	return b;
}

int main()
{
	int x = func(12, 15);
	printf("%d\n", x);
	return 0;
}