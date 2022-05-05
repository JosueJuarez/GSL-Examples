#include <stdio.h>
#include <vector>
#include "rapidcsv.h"
#include <gsl/gsl_multifit.h>

int main(int argc, char **argv)
{
	int i, n;
	double chisq;
	gsl_matrix *X, *cov;
	gsl_vector *y, *w, *c;

	rapidcsv::Document doc("/home/josue/Documentos/GitHub/GSL-Examples/Regresion Lineal/data.csv");
	std::vector<double> x_data = doc.GetColumn<double>("x");
	std::cout << "Read " << x_data.size() << " values." << std::endl;

	std::vector<double> y_data = doc.GetColumn<double>("y");
	std::cout << "Read " << y_data.size() << " values." << std::endl;

	std::vector<double> w_data = doc.GetColumn<double>("sigma");
	std::cout << "Read " << w_data.size() << " values." << std::endl;

	n = x_data.size();
	
	X = gsl_matrix_alloc(n, 3);

	y = gsl_vector_alloc(n);
	w = gsl_vector_alloc(n);
	c = gsl_vector_alloc (3);
	cov = gsl_matrix_alloc (3, 3);
	
	for (i = 0; i < n; i++)
	{
		gsl_matrix_set(X, i, 0, 1.0);
		gsl_matrix_set(X, i, 1, x_data[i]);
		gsl_matrix_set(X, i, 2, x_data[i]*x_data[i]);

		gsl_vector_set(y, i, y_data[i]);
		gsl_vector_set(w, i, w_data[i]);

	}

	{
	gsl_multifit_linear_workspace * work = gsl_multifit_linear_alloc(n, 3);
	gsl_multifit_wlinear(X, w, y, c, cov,
							&chisq, work);
	gsl_multifit_linear_free(work);

	#define C(i)(gsl_vector_get(c,(i)))
	#define COV(i,j)(gsl_matrix_get(cov,(i),(j)))
	}

	{
	printf ("# best fit: Y = %g + %g X + %g X^2\n",
	C(0), C(1), C(2));
	printf ("# covariance matrix:\n");
	printf ("[ %+.5e, %+.5e, %+.5e \n",
	COV(0,0), COV(0,1), COV(0,2));
	printf (" %+.5e, %+.5e, %+.5e \n",
	COV(1,0), COV(1,1), COV(1,2));
	printf (" %+.5e, %+.5e, %+.5e ]\n",
	COV(2,0), COV(2,1), COV(2,2));
	printf ("# chisq = %g\n", chisq);
	}

	gsl_matrix_free (X);
	gsl_vector_free (c);
	gsl_matrix_free (cov);

	return 0;
} 
