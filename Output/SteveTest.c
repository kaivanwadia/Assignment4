int branch(int a)
{
	int retVal = 0;
	int b = a;
	if (a < 0)
	{
		a = -1;
		b--;
	}
	else if (a>0)
	{
		retVal = 1;
		b++;
	}
	b++;
	retVal++;
	return retVal;
}