int loop(int a, int b)
{
	int x = a*3;
	int y = a*2;
	for (int i = 0; i < b; i++)
	{
		x = 10;
		for (int j = 0; j < a; j++)
		{
			y = y+2;
		}
	}
	return b*x;
}