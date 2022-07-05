#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

struct param_type {double m1; double m2; double m3; double k1; double k2; double k3; double k4;}; //Estructura para guardar los parámetros del sistema

//Definición del sistema de ecuaciones
int func(double t, const double y[], double f[], void *params)
{
	auto parametros = static_cast<param_type*>(params);
	(void)(t); /* avoid unused parameter warning */
	double m1 = parametros->m1;
	double m2 = parametros->m2;
	double m3 = parametros->m3;
	double k1 = parametros->k1;
	double k2 = parametros->k2;
	double k3 = parametros->k3;
	double k4 = parametros->k4;

	f[0] = y[3]/m1;
	f[1] = y[4]/m2;
	f[2] = y[5]/m3;
	f[3] = -k1*y[0] + k2*(y[1] - y[0]);
	f[4] = -k2*(y[1] - y[0]) + k3*(y[2] - y[1]);
	f[5] = -k3*(y[2] - y[1]) - k4*y[2];

	return GSL_SUCCESS;
}

//Jacobiano del sistema de ecuaciones
int jac(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
	auto parametros = static_cast<param_type*>(params);
	(void)(t); /* avoid unused parameter warning */
	double m1 = parametros->m1;
	double m2 = parametros->m2;
	double m3 = parametros->m3;
	double k1 = parametros->k1;
	double k2 = parametros->k2;
	double k3 = parametros->k3;
	double k4 = parametros->k4;

	double J03 = 1/m1;
	double J14 = 1/m2;
	double J25 = 1/m3;
	double J30 = -k1 - k2;
	double J31 = k2;
	double J40 = J31;
	double J41 = -k2 - k3;
	double J42 = k3;
	double J51 = J42;
	double J52 = -k3 - k4;

	gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 6, 6);
	gsl_matrix * m = &dfdy_mat.matrix;
	gsl_matrix_set(m, 0, 0, 0.0); gsl_matrix_set(m, 0, 1, 0.0); gsl_matrix_set(m, 0, 2, 0.0); gsl_matrix_set(m, 0, 3, J03); gsl_matrix_set(m, 0, 4, 0.0); gsl_matrix_set(m, 0, 5, 0.0);
	gsl_matrix_set(m, 1, 0, 0.0); gsl_matrix_set(m, 1, 1, 0.0); gsl_matrix_set(m, 1, 2, 0.0); gsl_matrix_set(m, 1, 3, 0.0); gsl_matrix_set(m, 1, 4, J14); gsl_matrix_set(m, 1, 5, 0.0);
	gsl_matrix_set(m, 2, 0, 0.0); gsl_matrix_set(m, 2, 1, 0.0); gsl_matrix_set(m, 2, 2, 0.0); gsl_matrix_set(m, 2, 3, 0.0); gsl_matrix_set(m, 2, 4, 0.0); gsl_matrix_set(m, 2, 5, J25);
	gsl_matrix_set(m, 3, 0, J30); gsl_matrix_set(m, 3, 1, J31); gsl_matrix_set(m, 3, 2, 0.0); gsl_matrix_set(m, 3, 3, 0.0); gsl_matrix_set(m, 3, 4, 0.0); gsl_matrix_set(m, 3, 5, 0.0);
	gsl_matrix_set(m, 4, 0, J40); gsl_matrix_set(m, 4, 1, J41); gsl_matrix_set(m, 4, 2, J42); gsl_matrix_set(m, 4, 3, 0.0); gsl_matrix_set(m, 4, 4, 0.0); gsl_matrix_set(m, 4, 5, 0.0);
	gsl_matrix_set(m, 5, 0, 0.0); gsl_matrix_set(m, 5, 1, J51); gsl_matrix_set(m, 5, 2, J52); gsl_matrix_set(m, 5, 3, 0.0); gsl_matrix_set(m, 5, 4, 0.0); gsl_matrix_set(m, 5, 5, 0.0);
	
	dfdt[0] = 0.0;
	dfdt[1] = 0.0;
	dfdt[2] = 0.0;
	dfdt[3] = 0.0;
	dfdt[4] = 0.0;
	dfdt[5] = 0.0;

	return GSL_SUCCESS;
}

double Energy(const double y[], void *params) //Función para calcular la energía del sistema
{
	auto parametros = static_cast<param_type*>(params);
	double m1 = parametros->m1;
	double m2 = parametros->m2;
	double m3 = parametros->m3;
	double k1 = parametros->k1;
	double k2 = parametros->k2;
	double k3 = parametros->k3;
	double k4 = parametros->k4;

	double E = (y[3]*y[3])/(2*m1) + (y[4]*y[4])/(2*m2) + (y[5]*y[5])/(2*m3)
					+ (1/2)*k1*y[0]*y[0] + (1/2)*k2*(y[1] - y[0])*(y[1] - y[0])
					+ (1/2)*k3*(y[2] - y[1])*(y[2] - y[1]) + (1/2)*k4*y[2]*y[2];

	return E;
}

int main(void)
{
	FILE *fptr;
	fptr = fopen("data.csv","w"); //Crea y abre el archivo txt

	if(fptr == NULL)
	{
	printf("Error!");   
 	exit(1);             
	}

	fprintf(fptr,"t,x1,x2,x3,E\n");

	struct param_type parametros = {1.0, 1.5, 2.0, 1.0, 0.5, 1.5, 2.0}; // Parámetros {m1, m2, m3, k1, k2, k3, k4}
	gsl_odeiv2_system sys = {func, jac, 6, &parametros}; //Definición del sistema de ecuaiones de gsl
	gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);

	int i;
	double t = 0.0, t1 = 15.0; //tiempo inicial y final
	double y[6] = {-0.5, 0.0, 1.5, 0.0, 1.0, -2.0}; //condiciones iniciales (x1(0), x2(0), x3(0), p1(0), p2(0), p3(0))

	for (i = 1; i <= 100; i++)
	{
		double ti = i * t1 / 100.0;
		int status = gsl_odeiv2_driver_apply(d, &t, ti, y); //Solución iterativa del sistema

		if(status != GSL_SUCCESS)
		{
			printf ("error, return value=%d\n", status);
			break;
		}
		
		double E = Energy(y, &parametros); //Calculo de la energía

		//Imprimir resultados
		fprintf(fptr, "%.5e,%.5e,%.5e,%.5e,%.5e\n", t, y[0], y[1], y[2], E);
	}

	fclose(fptr); //Cierra el archivo txt
	gsl_odeiv2_driver_free(d);

return 0;
}