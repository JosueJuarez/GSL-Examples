#include <stdio.h>
#include <cmath>

int C(int n, int k)
{
	int c;
	if(k == 0)
	{
		return 1;
	}
	else if(k == n)
	{
		return 1;
	}
	else if(k > n)
	{
		return 0;
	}
	else
	{
		return C(n-1,k-1) + C(n-1,k);
	}
	
}

int main()
{
	printf("C(8,4) = " "%d\n", C(8,4));
} 
