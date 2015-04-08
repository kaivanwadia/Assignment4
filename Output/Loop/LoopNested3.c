int nested(int a, int b, int c)
{
	int x = c*3;
	int y = c*2;
	for (int i = 0; i < b; i++)
	{
		x = x*2;
		for (int j = 0; j < a; j++)
		{
			y = b+2;
		}
	}
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