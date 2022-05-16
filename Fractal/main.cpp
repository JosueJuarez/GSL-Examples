#include <stdio.h>
//#include <complex.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
 
int main()
{
	FILE *fptr;
	int n = 500;
	int matriz[n][n];
	int iter;
	//double infty = 10000000.0;
	gsl_complex z0, zi, z, z2;
	fptr = fopen("data.txt","w"); //Crea y abre el archivo txt

	for(int x = 0; x < n; x++)
	{
		for(int y = 0; y < n; y++)
		{
			GSL_SET_COMPLEX(&z0, x, y);
			GSL_SET_COMPLEX(&z, 0, 0);
			//printf("%d" " " "%d" "|" "%f" " " "%f\n", x, y, GSL_REAL(z), GSL_IMAG(z));

			iter = 0;
			while(gsl_complex_abs(z) < 1e8 && iter < 1000)
			{
				z2 = gsl_complex_pow_real(z, 2);
				//printf("%f" " " "%f" "|" "%d\n", GSL_REAL(z2), GSL_IMAG(z2), iter);
				zi = gsl_complex_add(z2, z0);
				GSL_REAL(z) = GSL_REAL(zi);
				GSL_IMAG(z) = GSL_IMAG(zi);
				
				iter += 1;
			}
			
			
			if(gsl_complex_abs(z) > 1e8 || iter == 500)
			{
				matriz[x][y] = 0;
			}
			else
			{
				matriz[x][y] = 1;
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
				fprintf(fptr,"%i" " ", matriz[n][n]);
			}
			
		}
	}




	return 0;
}