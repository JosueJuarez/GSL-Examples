#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_math.h>

double	Pi(int n, gsl_rng * r) //aproximacion de pi con n iteraciones
{
	int c = 0;

	for(int i = 0; i < n; i++)
	{
		double x = gsl_rng_uniform(r);
		double y = gsl_rng_uniform(r);

		if(x*x + y*y < 1)
			{
				c += 1;
			}
	}

	return 4.*(double)c/(double)n;
}

int main(void)
{
	//Asignación de memoria
	const gsl_rng_type * T;
	gsl_rng * r;

	gsl_rng_env_setup();
	T = gsl_rng_default; //Tipo de generador
	r = gsl_rng_alloc(T); //asignacion de memoria al generador

	printf("GSL pi: " "%.18f\n", M_PI);
	printf("Aproximación de pi con 1000 iteraciones: " "%.18f\n", Pi(1000,r));

	//pi aprox. vs número de iteraciones

	FILE *fptr;
	fptr = fopen("data.csv","w"); //Crea y abre el archivo csv

	if(fptr == NULL)
	{
	printf("Error!");   
 	exit(1);             
	}

	fprintf(fptr,"n,pi\n");

	for(int i = 1; i < 1000; i++)
	{
		fprintf(fptr, "%d,%.18f\n", i, Pi(i,r));
	}

gsl_rng_free(r);

return 0;
}
