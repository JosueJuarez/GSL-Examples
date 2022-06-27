#include <stdio.h>
#include <cmath>

int Fact(int n)
{
	if(n == 0)
	{
		return 1;
	}

	else
	{
		return n*Fact(n-1);
	}
}

int main()
{
	int n = 5;

	printf("%d""! = ""%d\n", n, Fact(n));
	return 0;
} 
