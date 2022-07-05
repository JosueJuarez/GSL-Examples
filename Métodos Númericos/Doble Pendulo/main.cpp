#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_trig.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

struct param_type {double m1; double m2; double l1; double l2; double g;}; //Estructura para guardar los parámetros del sistema

//Definición del sistema de ecuaciones
int func(double t, const double y[], double f[], void *params)
{
	auto parametros = static_cast<param_type*>(params);
	(void)(t); /* avoid unused parameter warning */
	double m1 = parametros->m1;
	double m2 = parametros->m2;
	double l1 = parametros->l1;
	double l2 = parametros->l2;
	double g = parametros->g;

	double h1 = ( y[2]*y[3]*gsl_sf_sin(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );
	double h2 = ( m2*l2*l2*y[2]*y[2] + (m1+m2)*l1*l1*y[3]*y[3] - 2*m2*l1*l2*y[2]*y[3]*gsl_sf_cos(y[0]-y[1]) )/( 2*l1*l1*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );	

	f[0] = ( l2*y[2] - l1*y[3]*gsl_sf_cos(y[0]-y[1]) )/( l1*l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );
	f[1] = ( -m2*l2*y[2]*gsl_sf_cos(y[0]-y[1]) + (m1+m2)*l1*y[3] )/( m2*l1*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );
	f[2] = -(m1+m2)*g*l1*gsl_sf_sin(y[0]) - h1 + h2*gsl_sf_sin(2*(y[0]-y[1]));
	f[3] = -m2*g*l2*gsl_sf_sin(y[1]) + h1 - h2*gsl_sf_sin(2*(y[0]-y[1]));

	return GSL_SUCCESS;
}

//Jacobiano del sistema de ecuaciones
int jac(double t, const double y[], double *dfdy, double dfdt[], void *params)
{
	auto parametros = static_cast<param_type*>(params);
	(void)(t); /* avoid unused parameter warning */
	double m1 = parametros->m1;
	double m2 = parametros->m2;
	double l1 = parametros->l1;
	double l2 = parametros->l2;
	double g = parametros->g;

	gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 4, 4);
	gsl_matrix * m = &dfdy_mat.matrix;

	double J00 = ( -2*m2*gsl_sf_cos(y[0]-y[1])*( l2*y[2] - l1*y[3]*gsl_sf_cos(y[0]-y[1]) )*gsl_sf_sin(y[0]-y[1]) )/( l1*l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					+ ( y[3]*gsl_sf_sin(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J01 = -J00;

	double J02 = 1/( l1*l1*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J03 = ( -gsl_sf_cos(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J10 = -( 2*gsl_sf_cos(y[0]-y[1])*( l1*(m1+m2)*y[3] - l2*m2*y[2]*gsl_sf_cos(y[0]-y[1]) )*gsl_sf_sin(y[0]-y[1]) )/( l1*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					+ ( y[2]*gsl_sf_sin(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J11 = -J10;

	double J12 = ( -gsl_sf_cos(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J13 = ( m1+m2 )/( l2*l2*m2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J20 = ( ( l2*l2*m2*y[2]*y[2] + l1*l1*(m1+m2)*y[3]*y[3] - 2*l1*l2*m2*y[2]*y[3]*gsl_sf_cos(y[0]-y[1]) )*gsl_sf_cos(2*(y[0]-y[1])) )/( 2*l1*l1*l1*l1*l2*l2*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					- g*l1*(m1+m2)*gsl_sf_cos(y[0]-y[1]) + ( 2*m2*y[2]*y[3]*gsl_sf_cos(y[0]-y[1])*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					- ( y[2]*y[3]*gsl_sf_cos(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					- ( m2*gsl_sf_cos(y[0]-y[1])*( l2*l2*m2*y[2]*y[2] + l1*l1*(m1+m2)*y[3]*y[3] - 2*l1*l2*m2*y[2]*y[3]*gsl_sf_cos(y[0]-y[1]) )*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(2*(y[0]-y[1])) )/( l1*l1*l1*l1*l2*l2*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					+ ( m2*y[2]*y[3]*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(2*(y[0]-y[1])) )/( 2*l1*l1*l1*l2*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J21 = -( ( l2*l2*m2*y[2]*y[2] + l1*l1*(m1+m2)*y[3]*y[3] - 2*l1*l2*m2*y[2]*y[3]*gsl_sf_cos(y[0]-y[1]) )*gsl_sf_cos(2*(y[0]-y[1])) )/( 2*l1*l1*l1*l1*l2*l2*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					- ( 2*m2*y[2]*y[3]*gsl_sf_cos(y[0]-y[1])*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					+ ( y[2]*y[3]*gsl_sf_cos(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					+ ( m2*gsl_sf_cos(y[0]-y[1])*( l2*l2*m2*y[2]*y[2] + l1*l1*(m1+m2)*y[3]*y[3] - 2*l1*l2*m2*y[2]*y[3]*gsl_sf_cos(y[0]-y[1]) )*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(2*(y[0]-y[1])) )/( l1*l1*l1*l1*l2*l2*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					- ( m2*y[2]*y[3]*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(2*(y[0]-y[1])) )/( 2*l1*l1*l1*l2*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J22 = - ( y[3]*gsl_sf_sin(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					+ ( ( 2*l2*l2*m2*y[2] - 2*l1*l2*m2*y[3]*gsl_sf_cos(y[0]-y[1]) )*gsl_sf_sin(2*(y[0]-y[1])) )/( 4*l1*l1*l1*l1*l2*l2*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J23 = - ( y[2]*gsl_sf_sin(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					+ ( ( 2*l1*l1*(m1+m2)*y[3] - 2*l1*l2*m2*y[2]*gsl_sf_cos(y[0]-y[1]) )*gsl_sf_sin(2*(y[0]-y[1])) )/( 4*l1*l1*l1*l1*l2*l2*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J30 = J21;

	double J31 = -J30 - g*l2*m2*gsl_sf_cos(y[1]);

	double J32 = ( y[3]*gsl_sf_sin(y[0]-y[1]) )/( l1*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) )
					- ( ( 2*l2*l2*m2*y[2] - 2*l1*l2*m2*y[3]*gsl_sf_cos(y[0]-y[1]) )*gsl_sf_sin(2*(y[0]-y[1])) )/( 4*l1*l1*l1*l1*l2*l2*l2*l2*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) )*( m1 + m2*gsl_sf_sin(y[0]-y[1])*gsl_sf_sin(y[0]-y[1]) ) );

	double J33 = -J23;

	gsl_matrix_set(m, 0, 0, J00);
	gsl_matrix_set(m, 0, 1, J01);
	gsl_matrix_set(m, 0, 2, J02);
	gsl_matrix_set(m, 0, 3, J03);
	gsl_matrix_set(m, 1, 0, J10);
	gsl_matrix_set(m, 1, 1, J11);
	gsl_matrix_set(m, 1, 2, J12);
	gsl_matrix_set(m, 1, 3, J13);
	gsl_matrix_set(m, 2, 0, J20);
	gsl_matrix_set(m, 2, 1, J21);
	gsl_matrix_set(m, 2, 2, J22);
	gsl_matrix_set(m, 2, 3, J23);
	gsl_matrix_set(m, 3, 0, J30);
	gsl_matrix_set(m, 3, 1, J31);
	gsl_matrix_set(m, 3, 2, J32);
	gsl_matrix_set(m, 3, 3, J33);
	dfdt[0] = 0.0;
	dfdt[1] = 0.0;
	dfdt[2] = 0.0;
	dfdt[3] = 0.0;

	return GSL_SUCCESS;
}

// double Energy(const double y[], void *params) //Función para calcular la energía del sistema
// {
// 	auto parametros = static_cast<param_type*>(params);
// 	double m1 = parametros->m1;
// 	double m2 = parametros->m2;
// 	double k1 = parametros->k1;
// 	double k2 = parametros->k2;
// 	double k3 = parametros->k3;

// 	double E = (y[2]*y[2])/(2*m1) + (y[3]*y[3])/(2*m2)
// 					+ (1/2)*k1*y[0]*y[0] + (1/2)*k2*(y[1] - y[0])*(y[1] - y[0])
// 					+ (1/2)*k3*y[1]*y[1];

// 	return E;
// }

int main(void)
{
	FILE *fptr;
	fptr = fopen("data.csv","w"); //Crea y abre el archivo txt

	if(fptr == NULL)
	{
	printf("Error!");   
 	exit(1);             
	}

	fprintf(fptr,"t,x1,x2\n");

	struct param_type parametros = {1.0, 1.0, 1.0, 1.0}; // Parámetros {m1, m2, l1, l2}
	
	gsl_odeiv2_system sys = {func, jac, 4, &parametros}; //Definición del sistema de ecuaiones de gsl
	gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd, 1e-6, 1e-6, 0.0);

	int i;
	double t = 0.0, t1 = 15.0; //tiempo inicial y final
	double y[4] = {25.0, 60.0, 3.0, 6.0}; //condiciones iniciales (x1(0), x2(0), p1(0), p2(0))

	for (i = 1; i <= 100; i++)
	{
		double ti = i * t1 / 100.0;
		int status = gsl_odeiv2_driver_apply(d, &t, ti, y); //Solución iterativa del sistema

		if(status != GSL_SUCCESS)
		{
			printf ("error, return value=%d\n", status);
			break;
		}
		
		//double E = Energy(y, &parametros); //Calculo de la energía

		//Imprimir resultados
		fprintf(fptr, "%.5e,%.5e,%.5e\n", t, y[0], y[1]);
	}

	fclose(fptr); //Cierra el archivo txt
	gsl_odeiv2_driver_free(d);

return 0;
}