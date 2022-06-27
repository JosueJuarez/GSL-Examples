#include <stdio.h>
#include <cmath>

int main()
{
	int n = 50;
	int primos[n]; //lista de n números primos

	int k = 1; //conteo de números primos
	int x = 3; //candidato a número primo

	primos[k-1] = 2;
	printf("%d\n", 2);

	while(k <= n)
	{
		int primo = 1; //bandera
		int i = 0;

		while( i < k && primo == 1)
		{
			if(x % primos[i] == 0)
			{
				primo = 0;
			}
			i += 1;
		}

		if( primo == 1)
		{
			k += 1;
			printf("%d\n", x);
			primos[k-1] = x;
			x += 1;
		
		}
		else{x += 1;}
	}


	return 0;
} 
