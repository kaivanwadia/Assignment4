int sum(int a, int b)
{
	int c = b*2;
	int x = 0;
	int y = 0;
	for (int i = 0; i < b; i++)
	{
		x = a*a;
		y = x*c;
	}
	int ret = b*x;
	return ret;
}