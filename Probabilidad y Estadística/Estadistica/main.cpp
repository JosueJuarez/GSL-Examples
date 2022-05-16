#include <stdio.h>
#include <gsl/gsl_statistics.h>

//Estadística descriptiva

int main(void)
{
	double data[5] = {17.2, 18.1, 16.5, 18.3, 12.6}; //Datos
	double mean, variance, largest, smallest; //Variables

	mean     = gsl_stats_mean(data, 1, 5); //Promedio
	variance = gsl_stats_variance(data, 1, 5); //Varianza
	largest  = gsl_stats_max(data, 1, 5); //Valor máximo de los datos
	smallest = gsl_stats_min(data, 1, 5); //Valor mínimo de los datos

	printf("The dataset is %g, %g, %g, %g, %g\n",
			data[0], data[1], data[2], data[3], data[4]);

	printf ("The sample mean is %g\n", mean);
	printf ("The estimated variance is %g\n", variance);
	printf ("The largest value is %g\n", largest);
	printf ("The smallest value is %g\n", smallest);
  
return 0;
}
