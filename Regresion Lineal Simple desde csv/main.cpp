#include <iostream>
#include <vector>
#include "rapidcsv.h"
#include <gsl/gsl_fit.h>


int main()
{
	rapidcsv::Document doc("/home/josue/Documentos/GitHub/GSL-Examples/Regresion Lineal Simple desde csv/data.csv");
	std::vector<double> x = doc.GetColumn<double>("x");
	std::cout << "Read " << x.size() << " values." << std::endl;

	std::vector<double> y = doc.GetColumn<double>("y");
	std::cout << "Read " << y.size() << " values." << std::endl;


	double c0, c1, cov00, cov01, cov11, sumsq;

	gsl_fit_linear(&x.front(), 1, &y.front(), 1, x.size(),
		&c0, &c1, &cov00, &cov01, &cov11,
		&sumsq);

	printf ("# best fit: Y = %g + %g X\n", c0, c1);
	printf ("# covariance matrix:\n");
	printf ("# [ %g, %g\n# %g, %g]\n",
	cov00, cov01, cov01, cov11);
	printf ("# sumsq = %g\n", sumsq);


return 0;
}