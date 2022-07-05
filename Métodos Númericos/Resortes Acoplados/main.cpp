#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

// Sean m_1, m_2 las masas de dos partículas conectadas por tres resortes con constantes elásticas k_1, k_2 y k_3
//El Hamiltoniano del sistema es:
//
//H = \frac{p_{1}^{2}}{2m_1}  + \frac{p_{2}^{2}}{2m_2} + \frac{1}{2} k_1 x_{1}^{2} + \frac{1}{2} k_{2} (x_{2} - x_{1})^{2} + \frac{1}{2} k_3 x_{2}^{2},
//
// La dinámica del sistema esta dado por el sistema de ecuaciones

// \dot{x_1} = \frac{p_1}{m_1}
// \dot{x_2} = \frac{p_2}{m_2}
// \dot{p_1} = - k_{1} x_{1} + k_{2} (x_{2} - x_{1})
// \dot{p_2} = - k_{3} x_{2} - k_{2} (x_{2} - x_{1})
//
//Donde x_i y p_i son la coordenada y momento generalizado de cada particula.

struct param_type {double m1; double m2; double k1; double k2; double k3;}; //Estructura para guardar los parámetros del sistema

//Definición del sistema de ecuaciones
int func(double t, const double y[], double f[], void *params)
{
	auto parametros = static_cast<param_type*>(params);
	(void)(t); /* avoid unused parameter warning */
	double m1 = parametros->m1;
	double m2 = parametros->m2;
	double k1 = parametros->k1;
	double k2 = parametros->k2;
	double k3 = parametros->k3;

	f[0] = y[2]/m1;
	f[1] = y[3]/m2;
	f[2] = -k1*y[0] + k2*(y[1] - y[0]);
	f[3] = -k3*y[1] - k2*(y[1] - y[0]);

	return GSL_SUCCESS;
}

//Jacobiano del sistema de ecuaciones
int jac(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
	auto parametros = static_cast<param_type*>(params);
	(void)(t); /* avoid unused parameter warning */
	double m1 = parametros->m1;
	double m2 = parametros->m2;
	double k1 = parametros->k1;
	double k2 = parametros->k2;
	double k3 = parametros->k3;

	gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 4, 4);
	gsl_matrix * m = &dfdy_mat.matrix;
	gsl_matrix_set(m, 0, 0, 0.0);
	gsl_matrix_set(m, 0, 1, 0.0);
	gsl_matrix_set(m, 0, 2, 1/m1);
	gsl_matrix_set(m, 0, 3, 0.0);
	gsl_matrix_set(m, 1, 0, 0.0);
	gsl_matrix_set(m, 1, 1, 0.0);
	gsl_matrix_set(m, 1, 2, 0.0);
	gsl_matrix_set(m, 1, 3, 1/m2);
	gsl_matrix_set(m, 2, 0, -k1-k2);
	gsl_matrix_set(m, 2, 1, k2);
	gsl_matrix_set(m, 2, 2, 0.0);
	gsl_matrix_set(m, 2, 3, 0.0);
	gsl_matrix_set(m, 3, 0, k2);
	gsl_matrix_set(m, 3, 1, -k3-k2);
	gsl_matrix_set(m, 3, 2, 0.0);
	gsl_matrix_set(m, 3, 3, 0.0);
	dfdt[0] = 0.0;
	dfdt[1] = 0.0;
	dfdt[2] = 0.0;
	dfdt[3] = 0.0;

	return GSL_SUCCESS;
}

double Energy(const double y[], void *params) //Función para calcular la energía del sistema
{
	auto parametros = static_cast<param_type*>(params);
	double m1 = parametros->m1;
	double m2 = parametros->m2;
	double k1 = parametros->k1;
	double k2 = parametros->k2;
	double k3 = parametros->k3;

	double E = (y[2]*y[2])/(2*m1) + (y[3]*y[3])/(2*m2)
					+ (1/2)*k1*y[0]*y[0] + (1/2)*k2*(y[1] - y[0])*(y[1] - y[0])
					+ (1/2)*k3*y[1]*y[1];

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

	fprintf(fptr,"t,x1,x2,E\n");

	struct param_type parametros = {1.0, 1.5, 1.0, 0.5, 1.5,}; // Parámetros {m1, m2, k1, k2, k3}
	
	gsl_odeiv2_system sys = {func, jac, 4, &parametros}; //Definición del sistema de ecuaiones de gsl
	gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);

	int i;
	double t = 0.0, t1 = 15.0; //tiempo inicial y final
	double y[4] = {-0.5, 0.5, 2.0, -2.0}; //condiciones iniciales (x1(0), x2(0), p1(0), p2(0))

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
		fprintf(fptr, "%.5e,%.5e,%.5e,%.5e\n", t, y[0], y[1],E);
	}

	fclose(fptr); //Cierra el archivo txt
	gsl_odeiv2_driver_free(d);

return 0;
}