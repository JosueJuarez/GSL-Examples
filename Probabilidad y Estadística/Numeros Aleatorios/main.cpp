#include <stdio.h>
#include <gsl/gsl_rng.h>

//Genera números aleatorios en el rango [0,1)

int main(void)
{
	//Asignación de memoria
	const gsl_rng_type * T;
	gsl_rng * r;

	int i, n = 10;

	gsl_rng_env_setup();

	T = gsl_rng_default; //Tipo de generador
	r = gsl_rng_alloc(T); //asignacion de memoria al generador

	for (i = 0; i < n; i++)
	{
		double u = gsl_rng_uniform(r); //Genera un número aleatorio
		printf("%.5f\n", u);
	}

gsl_rng_free(r);

return 0;
}
