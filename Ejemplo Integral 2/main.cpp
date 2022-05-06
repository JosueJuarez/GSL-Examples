#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_sf_gamma.h>

//Calcula númericamente la integral
// I = \int_{\infty}^{\infty} \exp(-x^2)*(x^m + 1)dx
//El valor exacto de la integral depende del número m
// I = \sqrt{\pi} + \Gamma((m+1)/2), si m es par, \Gamma() es la función Gamma
// I = \sqrt{\pi}, si m es impar

//Definición de la función
double f(double x, void * params)
{
	int m = *(int *) params;
	double f = gsl_pow_int(x, m) + 1.0;
	return f;
}

int main (int argc, char *argv[])
{
	//Definición del tipo de integrador a usar
	gsl_integration_fixed_workspace * w;
	const gsl_integration_fixed_type * T = gsl_integration_fixed_hermite;
	//Parámetros
	//Para que el integrador converga se debe cumplir la siguiente relación
	// n >= (m+1)/2
	int m = 10;
	int n = 6;
	double expected, result;
	gsl_function F;
	if (argc > 1)
	m = atoi(argv[1]);
	if (argc > 2)
	n = atoi(argv[2]);
	w = gsl_integration_fixed_alloc(T, n, 0.0, 1.0, 0.0, 0.0);
	F.function = &f;
	F.params = &m;

	gsl_integration_fixed(&F, &result, w); //Integra

	//Solución exacta para comparar
	if (m % 2 == 0)
	expected = M_SQRTPI + gsl_sf_gamma(0.5*(1.0 + m));
	else
	expected = M_SQRTPI;

	//Imprime resultados
	printf ("m = %d\n", m);
	printf ("intervals = %zu\n", gsl_integration_fixed_n(w));
	printf ("result = % .18f\n", result);
	printf ("exact result = % .18f\n", expected);
	printf ("actual error = % .18f\n", result - expected);
	gsl_integration_fixed_free (w);

return 0;
}