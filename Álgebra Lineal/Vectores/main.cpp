#include <stdio.h>
#include <gsl/gsl_vector.h>

int main(void)
{
	int i;
	int n = 5;
	//Crear vectores de dimensión n
	gsl_vector * v = gsl_vector_alloc(n);
	gsl_vector * w = gsl_vector_alloc(n);
	gsl_vector * vt = gsl_vector_alloc(n);

	//Rellenar los vetores con valores
	for(i = 0; i < n; i++)
	{
	gsl_vector_set(v, i, 1.23 + i);
	gsl_vector_set(w, i, -5.23 + i);
    }

    //Copia el vector v en el vector temporal vt
    gsl_vector_memcpy(vt, v);

    //imprimir v y w
    printf("v =      w =\n");
	for(i = 0; i < n; i++)
    {
	printf("(%g) (%g)\n", gsl_vector_get (v, i), gsl_vector_get (w, i));
    }
    printf("---------------\n");

//------------------
    gsl_vector_swap_elements(vt, 0, 4); // Inercambia el elemento 0 con el 4 de v
    printf("Elemento 0 intecambiado con elemento 4 (de v)\n");
    printf("v' =\n");
    for(i = 0; i < n; i++)
    {
	printf("(%g)\n", gsl_vector_get (vt, i));
    }
    printf("---------------\n");
    gsl_vector_memcpy(vt, v);

//------------------
  	gsl_vector_reverse(vt); //invierte el orden del vector v
    printf("Vector v en orden inverso\n");
    printf("v' =\n");
    for(i = 0; i < n; i++)
    {
	printf("(%g)\n", gsl_vector_get (vt, i));
    }
    printf("---------------\n");
    gsl_vector_memcpy(vt, v);

//------------------
    gsl_vector_add(vt, w); // v + w
    printf("v + w =\n");
    for(i = 0; i < n; i++)
    {
	printf("(%g)\n", gsl_vector_get (vt, i));
    }
    printf("---------------\n");
    gsl_vector_memcpy(vt, v);

//------------------
    gsl_vector_sub(vt, w); // v - w
    printf("v - w =\n");
    for(i = 0; i < n; i++)
    {
	printf("(%g)\n", gsl_vector_get (vt, i));
    }
    printf("---------------\n");
    gsl_vector_memcpy(vt, v);

//------------------
    gsl_vector_mul(vt, w); //Multiplica las componentes de v por los elementos de w
    printf("v * w =\n");
    for(i = 0; i < n; i++)
    {
	printf("(%g)\n", gsl_vector_get (vt, i));
    }
    printf("---------------\n");
    gsl_vector_memcpy(vt, v);

//------------------
    gsl_vector_div(vt, w); //Divide las componentes de v por los elementos de w
    printf("v / w =\n");
    for(i = 0; i < n; i++)
    {
	printf("(%g)\n", gsl_vector_get (vt, i));
    }
    printf("---------------\n");
    gsl_vector_memcpy(vt, v);

 //----------------
    //Escalar un vector
    gsl_vector_scale(vt, 5.0); // v -> 5*v
    printf("5v =\n");
    for(i = 0; i < n; i++)
    {
	printf("(%g)\n", gsl_vector_get (vt, i));
    }
    printf("---------------\n");
    gsl_vector_memcpy(vt, v);

//----------------
    gsl_vector_add_constant(vt, 5); // v -> v_i + 5
    printf("v + 5 =\n");
    for(i = 0; i < n; i++)
    {
	printf("(%g)\n", gsl_vector_get (vt, i));
    }
    printf("---------------\n");
    gsl_vector_memcpy(vt, v);

//----------------
	double s = gsl_vector_sum(v); //Suma los elementos de v
	printf("suma = %g\n", s);
    printf("---------------\n");

//----------------
    //Producto escalar
    gsl_vector_mul(vt, w);
    s = gsl_vector_sum(vt);
	printf("v.w = %g\n", s);
	printf("---------------\n");
	gsl_vector_memcpy(vt, v);

//----------------
	//Realiza la operación v -> a*w + b*v, a y b son escalares
	gsl_vector_axpby(2.0, w, 5.0, vt); // v -> 2*w + 5*v
    printf("2*w + 5*v =\n");
    for(i = 0; i < n; i++)
    {
	printf("(%g)\n", gsl_vector_get (vt, i));
    }
    printf("---------------\n");
    gsl_vector_memcpy(vt, v);

//----------------
    s = gsl_vector_max(v); // max(v)
	printf("max(v) = %g\n", s);
    printf("---------------\n");

//----------------
    s = gsl_vector_min(v); // min(v)
	printf("min(v) = %g\n", s);
    printf("---------------\n");




	gsl_vector_free (v);
	gsl_vector_free (w);
	gsl_vector_free (vt);

return 0;
}
