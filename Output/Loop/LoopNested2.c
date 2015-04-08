int nested(int a, int b)
{
	int x = a*3;
	int y = a*2;
	for (int i = 0; i < b; i++)
	{
		x = a*2;
		for (int j = 0; j < a; j++)
		{
			y = b+2;
		}
	}
	return x*y;
}