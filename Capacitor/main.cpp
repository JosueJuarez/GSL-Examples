#include <stdio.h>
#include <cmath>

//Campo eléctrico debido a un dipolo, las coordenadas de las cargas son
//q2 en (-1,0) y q1 en (1,0)

double Ex(double q, double x, double y, double xi, double yi) //Componente Ex del campo en un punto (xi,yi) debido a la particula en (x,y)
{
	double r = sqrt((x-xi)*(x-xi) + (y-yi)*(y-yi));
	return (q*(xi - x))/(r*r*r);
}

double Ey(double q, double x, double y, double xi, double yi) //Componente Ex del campo en un punto (xi,yi) debido a la particula en (x,y)
{
	double r = sqrt((x-xi)*(x-xi) + (y-yi)*(y-yi));
	return (q*(yi - y))/(r*r*r);
}

int main()
{

	FILE *fptr;
	fptr = fopen("data.csv","w"); //Crea y abre el archivo txt

	if(fptr == NULL)
	{
	printf("Error!");   
 	exit(1);             
	}

	fprintf(fptr,"x,y,Ex,Ey,E\n");


	double q = 2.0; // carga
	double xq = 1.0; //coordenada x de las cargas

	//meshgrid
	double dx = 0.5;
	int L = 20;
	int n = 2*L - 1; // n = L/dx - 1

	// separación de las cargas
	double dq = 0.1;
	int Lq = 4;
	int nq = 10*Lq - 1;


	double xi, yi, Exi, Eyi, E;

	for(int i = 0; i < n + 2; i++)
	{
		xi = -10.0 + i*dx;

		for(int j = 0; j < n + 2; j++)
		{
			yi = -10.0 + j*dx;


			Exi = 0;
			Eyi = 0;

			for(int k = 0; k < nq + 2; k++)
			{
				Exi += Ex(q, xq, -2 + k*dq, xi, yi) + Ex(-q, -xq, -2 + k*dq, xi, yi);
				Eyi += Ey(q, xq, -2 + k*dq, xi, yi) + Ey(-q, -xq, -2 + k*dq, xi, yi);
			}

			E = sqrt(Exi*Exi + Eyi*Eyi);
			fprintf(fptr, "%.5e,%.5e,%.5e,%.5e,%.5e\n", xi, yi, Exi, Eyi, E);

		}
	}

	return 0;
} 
