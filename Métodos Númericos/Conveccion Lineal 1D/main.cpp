#include <stdio.h>
#include <gsl/gsl_vector.h>

double Pulso(double x0, double x1, double x)
{
	if((x < x0) || (x > x1)){return 0.0;}
	
	else{return 1.0;}

}

int main()
{
	double L = 2.0; //el tamaño del intervalo en x
	double nx = 41.0; //número total en que se discretiza x
	double dx = L/(nx-1.0); //distancia entre cada punto discretizado
	double T = 1.0; //intervalo total de tiempo
	double nt = 51.0; //número de veces que se discretiza la variable tiempo
	double dt = T/(nt-1.0); //tamaño de los intervalos de tiempo
	double c = 1.0; //velocidad de la onda

	gsl_vector * x = gsl_vector_alloc(nx);
	gsl_vector * u = gsl_vector_alloc(nx);
	gsl_vector * u0 = gsl_vector_alloc(nx);
	gsl_vector * un = gsl_vector_alloc(nx);

	for(int i = 0; i < nx; i++)
	{
		gsl_vector_set(x, i, 0.0 + i*dx); //espacio lineal para la variable x
		gsl_vector_set(u, i, Pulso(0.5, 1.0, gsl_vector_get(x, i))); //crea el perfil del pulso.
	}

	gsl_vector_memcpy(u0, u); //copia del pulso inicial

	for(int n = 0; n < nt; n++) //un loop nt veces
	{
		gsl_vector_memcpy(un, u); //copia los elementos del vector u al vector temporal un

		for(int i = 1; i < nx; i++)
		{
			double u_i = gsl_vector_get(un, i) - c*dt*( gsl_vector_get(un, i) - gsl_vector_get(un, i-1) )/dx;
			gsl_vector_set(u, i, u_i);
		}
	}

	FILE *fptr;
	fptr = fopen("data.csv","w"); //Crea y abre el archivo csv

	if(fptr == NULL)
	{
	printf("Error!");   
 	exit(1);             
	}

	fprintf(fptr,"x,u0,uf\n");

	for(int i = 0; i < nx; i++)
	{
		fprintf(fptr, "%.5e,%.5e,%.5e\n", gsl_vector_get(x, i), gsl_vector_get(u0, i), gsl_vector_get(u, i));
	}


    gsl_vector_free(x);
    gsl_vector_free(u);
    gsl_vector_free(u0);
    gsl_vector_free(un);

	return 0;
} 
