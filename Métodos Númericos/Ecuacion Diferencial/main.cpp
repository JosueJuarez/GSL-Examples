#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

//Resuelve la ecuación diferencial no lineal de segundo orden
// u''(t) + \mu*u'(t)*(u^{2}(t) - 1) + u(t) = 0
//Mediante el cambio de variable u' = v, se obtiene un sistema de ecuaciones diferenciales de primer orden
//
// u' = v
// v' = -u + \mu*v*(1 - u^{2})
//La solución comienza desde (u,v) = (1,0) en t=0 hasta t=100

//Definición del sistema de ecuaciones
int func(double t, const double y[], double f[], void *params)
{
	(void)(t); /* avoid unused parameter warning */
	double mu = *(double *)params;
	f[0] = y[1];
	f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);
	return GSL_SUCCESS;
}

//Jacobiano del sistema de ecuaciones
int jac(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
	(void)(t); /* avoid unused parameter warning */
	double mu = *(double *)params;
	gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
	gsl_matrix * m = &dfdy_mat.matrix;
	gsl_matrix_set(m, 0, 0, 0.0);
	gsl_matrix_set(m, 0, 1, 1.0);
	gsl_matrix_set(m, 1, 0, -2.0*mu*y[0]*y[1] - 1.0);
	gsl_matrix_set(m, 1, 1, -mu*(y[0]*y[0] - 1.0));
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

	fprintf(fptr,"t,u,u'\n");

	double mu = 10;
	gsl_odeiv2_system sys = {func, jac, 2, &mu}; //Definición del sistema de ecuaiones de gsl
	gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);

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
	gsl_odeiv2_driver_free(d);

return 0;
}