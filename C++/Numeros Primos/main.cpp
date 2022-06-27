#include <stdio.h>
#include <cmath>

int main()
{
	int n = 50;
	int primos[n]; //lista de números primos

	primos.push(2);
	printf("%d\n", 2);

	int k = 1;
	int x = 3;

	while(k <= n)
	{
		int primo = 1; //bandera
		int i = 0;

		while( i < k && primo == 1)
		{
			if(x % primos[i] == 0)
			{
				primo == 0;
			}
			i += 1;
		}

		if( primo == 1)
		{
			printf("%d\n", x);
			primos.push(x);
			x += 1;
			k += 1;
		}
		else{x += 1}
	}


	return 0;
} 
