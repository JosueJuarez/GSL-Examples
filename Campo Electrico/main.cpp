#include <stdio.h>
#include <cmath>

//Campo eléctrico debido a un dipolo, las coordenadas de las cargas son
//q2 en (-1,0) y q1 en (1,0)

double Ex(double q, double x, double xi, double yi)
{
	double r = sqrt((x-xi)*(x-xi) + yi*yi);
	return (q*(xi - x))/(r*r*r);
}

double Ey(double q, double x, double xi, double yi)
{
	double r = sqrt((x-xi)*(x-xi) + yi*yi);
	return (q*(yi))/(r*r*r);
}

int main()
{

	FILE *fptr;
	fptr = fopen("data.csv","w"); //Crea y abre el archivo csv

	if(fptr == NULL)
	{
	printf("Error!");   
 	exit(1);             
	}

	fprintf(fptr,"x,y,Ex,Ey,E\n");


	double q = 2.0;
	double q1x = 1.0;
	double dx = 0.5;
	int L = 20;
	int n = 2*L - 1; // n = L/dx - 1
	double xi, yi, Exi, Eyi, E;

	for(int i = 0; i < n + 2; i++)
	{
		xi = -10.0 + i*dx;

		for(int j = 0; j < n + 2; j++)
		{
			yi = -10.0 + j*dx;

			Exi = Ex(q, q1x, xi, yi) + Ex(-q, -q1x, xi, yi);
			Eyi = Ey(q, q1x, xi, yi) + Ey(-q, -q1x, xi, yi);
			E = sqrt(Exi*Exi + Eyi*Eyi);

			fprintf(fptr, "%.5e,%.5e,%.5e,%.5e,%.5e\n", xi, yi, Exi, Eyi, E);

		}
	}

	return 0;
} 
