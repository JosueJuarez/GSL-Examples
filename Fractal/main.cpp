#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int main()
{
	FILE *fptr;
	int n = 500;
	int matriz[n][n];
	int iter;
	gsl_complex z0, z;
	fptr = fopen("data.txt","w"); //Crea y abre el archivo txt

	for(int x = 0; x < n; x++)
	{
		for(int y = 0; y < n; y++)
		{
			GSL_REAL(z0) = x; //parte real
			GSL_IMAG(z0) = y; //parte imaginaria
			z = z0;
			while(gsl_complex_abs(z) < 4 && iter < 1000)
			{
				z = gsl_complex_add(gsl_complex_pow_real(z, 2),z0);
				iter += 1;
			}

			if(iter == 1000)
			{
				matriz[x][y] = 1;
			}
			else
			{
				matriz[x][y] = 0;
			}
			
		}
	}

	for(int x = 0; x < n; x++)
	{
		for(int y = 0; y < n; y++)
		{
			if(y==n-1)
			{
				fprintf(fptr,"%i\n", matriz[n][n]); //Escribe los valores en el txt	
			}
			else
			{
				fprintf(fptr,"%i", matriz[n][n]);
			}
			
		}
	}




	return 0;
}