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
			if(w < a + b)
			{
				a = 15 * b;
				w += 1; 
				q -= 1 + a; // dead
				b = a * 2; // dead
			}
			else
			{
				b *= -1; // dead
			}
		}
	}

	if( a < 5)
	{
		q = 10 * a; // dead
		w = 15 * w;
		a = 100 + b;
	}
	else
	{
		a = 5 * q;
		q = w * 5; // dead
		b = 4 + 2 + w + a; // dead
	}

	b = w * a;

	return b;
}

int main()
{
	int x = func(12, 15);
	printf("%d\n", x);
	return 0;
}