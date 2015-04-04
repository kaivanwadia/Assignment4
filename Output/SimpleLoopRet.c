int sum(int a, int b)
{
	int i;
	int res = 1;
	int x = b * 2;
	for (i = a; i < b; i++)
	{
		res *= i;
		x = x * 2;
	}
	return res;
}
