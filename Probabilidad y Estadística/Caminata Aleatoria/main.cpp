#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

//Caminata aleatoria en dos dimensiones.

int main(void)
{
  //Crear y abrir arhivo .txt
  FILE *fptr;
  fptr = fopen("data.txt","w"); //Crea y abre el archivo txt
  if(fptr == NULL)
  {
    printf("Error!");   
    exit(1);             
  }

  //Definición de los parámetros
  int i;
  double x = 0, y = 0, dx, dy;

  //Generador de números aleatorios
  const gsl_rng_type * T;
  gsl_rng * r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);

  fprintf (fptr, "%f %f\n", x, y); //Imprime coordenadas iniciales

  for (i = 0; i < 10; i++)
  {
    gsl_ran_dir_2d (r, &dx, &dy); //Caminata aleatoria
    x += dx; y += dy; //Nueva posición
    fprintf (fptr, "%f %f\n", x, y);
  }

fclose(fptr); //Cierra el archivo txt
gsl_rng_free (r);

return 0;
}