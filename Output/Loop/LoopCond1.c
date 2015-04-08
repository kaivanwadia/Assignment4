int sum(int a, int b)
{
	int x = a * 2;
	int y = b + 1;
	for (int i = 0; i < 10; i++)
	{
		if (x > 3)
		{
			x = b*3;
		}
		else
		{
			y = a + 2;
		}
	}
	return x * 2;
}