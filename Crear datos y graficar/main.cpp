#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_trig.h>

int main()
{
   double y;
   FILE *fptr;

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen("/home/josue/Documentos/GitHub/GSL-Examples/Crear datos y graficar/build/data.txt","w");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }

   for(double i = 0; i < 2*M_PI; i+=0.1){
      y = gsl_sf_sin(i);
      fprintf(fptr,"%f" " " "%f" "\n", i, y);
   }

   fclose(fptr);

   return 0;
} 
