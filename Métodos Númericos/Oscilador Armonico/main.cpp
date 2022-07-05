#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

//Resuelve la ecuación diferencial del oscilador armónico y'' + w^{2} y = 0, transformando a un sistema de dos ecuaciones diferenciales
//	y' = u
//	u' = -w^{2} y
//con condiciones iniciales y(0) = 1; u(0) = 0

//Definición del sistema de ecuaciones
int func(double t, const double y[], double f[], void *params)
{
	(void)(t); /* avoid unused parameter warning */
	double w = *(double *)params;
	f[0] = y[1];
	f[1] = -w*w*y[0];
	return GSL_SUCCESS;
}

//Jacobiano del sistema de ecuaciones
int jac(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
	(void)(t); /* avoid unused parameter warning */
	double w = *(double *)params;
	gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
	gsl_matrix * m = &dfdy_mat.matrix;
	gsl_matrix_set(m, 0, 0, 0.0);
	gsl_matrix_set(m, 0, 1, 1.0);
	gsl_matrix_set(m, 1, 0, -w*w);
	gsl_matrix_set(m, 1, 1, 0.0);
	dfdt[0] = 0.0;
	dfdt[1] = 0.0;

	return GSL_SUCCESS;
}

int main (void)
{
	FILE *fptr;
	fptr = fopen("data.csv","w"); //Crea y abre el archivo txt

	if(fptr == NULL)
	{
	printf("Error!");   
 	exit(1);             
	}

	fprintf(fptr,"t,y,y'\n");

	double w = 5;
	gsl_odeiv2_system sys = {func, jac, 2, &w}; //Definición del sistema de ecuaiones de gsl
	gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk1imp, 1e-6, 1e-6, 0.0);

	int i;
	double t = 0.0, t1 = 100.0; //tiempo inicial y final
	double y[2] = { 1.0, 0.0 }; //condiciones iniciales

	for (i = 1; i <= 100; i++)
	{
		double ti = i * t1 / 100.0;
		int status = gsl_odeiv2_driver_apply(d, &t, ti, y); //Solución iterativa del sistema

		if(status != GSL_SUCCESS)
		{
			printf ("error, return value=%d\n", status);
			break;
		}
		
		//Imprimir resultados
		fprintf(fptr, "%.5e,%.5e,%.5e\n", t, y[0], y[1]);
	}

	fclose(fptr); //Cierra el archivo txt
	gsl_odeiv2_driver_free(d);

return 0;
}