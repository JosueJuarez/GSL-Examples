#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>

//Calcula el valor de la función de Bessel

int
main (void)
{
double x = 5.0;
double y = gsl_sf_bessel_J0 (x); //Caculo del valor
printf ("J0(%g) = %.18e\n", x, y);
return 0;
}