#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_trig.h>

//Calcula los valores de la función sen(x) en el rango [0,2*pi)

int main()
{
   double y;
   FILE *fptr;

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen("/home/josue/Documentos/GitHub/GSL-Examples/Crear datos y graficar/build/data.txt","w"); //Crea y abre el archivo txt

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   for(double i = 0; i < 2*M_PI; i+=0.1){
      y = gsl_sf_sin(i); //Calculo del senx
      fprintf(fptr,"%f" " " "%f" "\n", i, y); //Escribe los valores en el txt
   }

   fclose(fptr); //Cierra el archivo txt

   return 0;
} 
