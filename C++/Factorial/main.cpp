#include <stdio.h>
#include <cmath>

int Fib(int n)
{
	if(n == 0)
	{
		return 0;
	}

	else if(n == 1)
	{
		return 1;
	}

	else
	{
		return Fib(n-1) + Fib(n-2);
	}
}

int main()
{
	int n = 20;

	for(int i = 0; i < 20; i++)
	{
		printf("%d\n", Fib(i));
	}
	return 0;
} 
