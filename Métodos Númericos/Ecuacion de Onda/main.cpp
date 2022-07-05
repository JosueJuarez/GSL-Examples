#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_trig.h>
#include <gsl/gsl_vector.h>

struct param_type {double m1; double m2; double l1; double l2; double g;};

double f(double x)
{
	return gsl_sf_sin(M_PI*x);	
}

double g(double x)
{
	return 0.0;
}


int main()
{
	double L = 1.0; //el tamaño del intervalo en x
	double nx = 9.0; //número total en que se discretiza x
	double dx = L/(nx+1.0); //distancia entre cada punto discretizado
	//double T = 1.0; //intervalo total de tiempo
	double nt = 20.0; //número de veces que se discretiza la variable tiempo
	double dt = 0.05; //tamaño de los intervalos de tiempo
	double c = 2.0; //velocidad de la onda
	double lambda = c*dt/dx; // para que la convergencia sea estable, lambda <= 1

	gsl_vector * x = gsl_vector_alloc(nx+2);
	gsl_vector * u = gsl_vector_alloc(nx+2);
	gsl_vector * w = gsl_vector_alloc(nx+2);
	gsl_vector * u0 = gsl_vector_alloc(nx+2);
	gsl_vector * utemp = gsl_vector_alloc(nx+2);

	for(int i = 0; i < nx + 2; i++)
	{
		gsl_vector_set(x, i, 0.0 + i*dx); //espacio lineal para la variable x
		gsl_vector_set(u, i, f(gsl_vector_get(x, i))); //crea el perfil del pulso.
	}

	//rellenar el vector de condiciones iniciales
	gsl_vector_set(w, 0, 0);
	gsl_vector_set(w, nx+1, 0);
	for(int i = 1; i < nx + 1; i++)
	{
		double w_i = (1 - lambda*lambda)*gsl_vector_get(u,i) + (0.5)*lambda*lambda*( gsl_vector_get(u,i+1) + gsl_vector_get(u,i-1) ) + dt*g(gsl_vector_get(x,i));
		gsl_vector_set(w, i, w_i);
	}

	gsl_vector_memcpy(u0, u); //copia del pulso inicial

	for(int n = 1; n < nt; n++) //un loop nt veces
	{
		for(int i = 1; i < nx+1; i++)
		{
			double ut = 2*(1 - lambda*lambda)*gsl_vector_get(w,i) + lambda*lambda*( gsl_vector_get(w,i+1) + gsl_vector_get(w,i-1) ) - gsl_vector_get(u,i);
			gsl_vector_set(utemp, i, ut);
		}
		gsl_vector_memcpy(u, w);
		gsl_vector_memcpy(w, utemp); 
	}

	FILE *fptr;
	fptr = fopen("data.csv","w"); //Crea y abre el archivo csv

	if(fptr == NULL)
	{
	printf("Error!");   
 	exit(1);             
	}

	fprintf(fptr,"x,u0,up\n");

	for(int i = 0; i < nx+2; i++)
	{
		fprintf(fptr, "%.5e,%.5e,%.5e\n", gsl_vector_get(x, i), gsl_vector_get(u0, i), gsl_vector_get(u, i));
	}

	fclose(fptr); //Cierra el archivo txt

    gsl_vector_free(x);
    gsl_vector_free(u);
    gsl_vector_free(u0);
    gsl_vector_free(w);
    gsl_vector_free(utemp);

	return 0;
} 
