//Función invert_a_matrix fue tomada de https://gist.github.com/bjd2385/7f4685e703f7437e513608f41c65bbd7

#include <iostream>
#include <vector>
#include "rapidcsv.h"
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_linalg.h>

gsl_matrix *invert_a_matrix(gsl_matrix *matrix);

gsl_matrix *invert_a_matrix(gsl_matrix *matrix)
{
    gsl_permutation *p = gsl_permutation_alloc(3); //size
    int s;

    // Compute the LU decomposition of this matrix
    gsl_linalg_LU_decomp(matrix, p, &s);

    // Compute the  inverse of the LU decomposition
    gsl_matrix *inv = gsl_matrix_alloc(3, 3);
    gsl_linalg_LU_invert(matrix, p, inv);

    gsl_permutation_free(p);

    return inv;
}


int main()
{
	int i;
	gsl_matrix *X, *Y, *C, *invC, *XTY, *Xp;

	rapidcsv::Document doc("/home/josue/Documentos/GitHub/GSL-Examples/Regresion Lineal 2/data.csv");
	std::vector<double> x_data = doc.GetColumn<double>("x");
	std::cout << "Read " << x_data.size() << " values." << std::endl;

	std::vector<double> y_data = doc.GetColumn<double>("y");
	std::cout << "Read " << y_data.size() << " values." << std::endl;

	X = gsl_matrix_alloc(x_data.size(), 3);
	Y = gsl_matrix_alloc(y_data.size(), 1);
	C = gsl_matrix_alloc(3,3);
	XTY = gsl_matrix_alloc(3,1);
	Xp = gsl_matrix_alloc(3,1);

	for (i = 0; i < x_data.size(); i++)
	{
		gsl_matrix_set(X, i, 0, 1.0);
		gsl_matrix_set(X, i, 1, x_data[i]);
		gsl_matrix_set(X, i, 2, x_data[i]*x_data[i]);

		gsl_matrix_set(Y, i, 0, y_data[i]);
	}

	gsl_matrix_set_zero(C);
	gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, X, X, 0, C);

	invC = invert_a_matrix(C);

	gsl_matrix_set_zero(XTY);
	gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, X, Y, 0, XTY);	

	gsl_matrix_set_zero(Xp);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, invC, XTY, 0, Xp);

	#define imprimir(i)(gsl_matrix_get(Xp,(i),(0)))
	printf ("# best fit: Y = %g + %g X + %g X^2\n",
	imprimir(0), imprimir(1), imprimir(2));

return 0;
}