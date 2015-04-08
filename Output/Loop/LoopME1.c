int sum(int a, int b)
{
	int x = a * 2;
	for (int i = 0; i < 10; i++)
	{
		if (i == a)
		{
			x = a*a;
			break;
		}
		else
		{
			x = b*b;
		}
	}
	return x * 2;
}