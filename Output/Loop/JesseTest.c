int sum(int c)
{
	int y = c*2;
	int x = y+1;
	if (c == 1)
	{
L1:		x = x+1;
		if (c == 2)
		{
			goto L2;
		}
		else
		{
			goto L3;
		}
	}
	else
	{
L2:		x = x*2;
		if (c == 2)
		{
			goto L1;
		}
		else
		{
			goto L3;
		}
	}
L3:	return x+2;
}