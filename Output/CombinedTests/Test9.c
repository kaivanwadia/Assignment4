#include <stdio.h>

// 0 Dead codes
int func(int a, int b)
{
	int q = a * b;
	int w = b * q;
	int c = a + b * q + q;
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
	for(int i = 0; i < b; i++)
	{
		q *= 2;
		if(q%3 == 0)
		{
			w += a + b * q;
		}
		else if(q%3 == 1)
		{
			a += -1;
		}
		else
		{
			b += 2;
		}
	}
	for(int k = a; k > 0; k--)
	{
		w -= k;
		q += (a * w) - (b * w);
		c = a * b + 22;
	}

	if( a < 5)
	{
		q = 10;
		w = 15;
		a = 100;
	}
	else
	{
		a = 5;
		q = w * 5;
		b = 4 + 2 + w + a;
	}

	b = w * q + c;

	return b;
}

int main()
{
	int x = func(2, 11);
	printf("%d\n", x);
	return 0;
}