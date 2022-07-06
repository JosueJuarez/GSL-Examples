#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

void PrintMatrix(gsl_matrix* M) //Funcion para imprimir los valores de la matriz en la terminal
{
    //obtener las dimensiones de la matriz M
    int m = M->size1;
    int n = M->size2;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(j == n-1)
                printf("%g\n", gsl_matrix_get(M,i,j)); //gsl_matrix_get obtiene el elemento en la posicion i,j de la matriz dada
            else
                printf("%g" " ", gsl_matrix_get(M,i,j));
        }
    }


}

int main(void)
{
	
	int m = 5;
    int n = 3;


    gsl_matrix * A = gsl_matrix_alloc(m, n); //Asigna memoria para una matriz de tamaño m x n
    gsl_matrix * B = gsl_matrix_alloc(m, n);
    gsl_matrix * C = gsl_matrix_alloc(n, n);
    gsl_matrix * D = gsl_matrix_alloc(n, m);
    gsl_matrix * E = gsl_matrix_alloc(m, n);

    //Rellenar la matriz manualente
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        gsl_matrix_set(A, i, j, 0.23 + 100*i + j); //asigna un valor en la posicion (i,j) de la matriz A

    gsl_matrix_set_all(B, 7.52); //asigna a todos los elementos de la matriz dada el valor dado
    gsl_matrix_set_zero(C); //asigna todos los valores a 0 de la matriz dada
    gsl_matrix_set_identity(D); //Crea una matriz identidad (aunque la matriz no sea cuadrada)

    printf("Matriz creada manualmente:\n");
    printf("A = \n");
    PrintMatrix(A);

    printf("----------\n");
    
    printf("Matriz constante:\n");
    printf("B = \n");
    PrintMatrix(B);

    printf("----------\n");
    printf("Matriz de ceros:\n");
    printf("C = \n");
    PrintMatrix(C);

    printf("----------\n");
    printf("Matriz identidad:\n");
    printf("D = \n");
    PrintMatrix(D);

    printf("----------\n");

    //-----------------------------

    gsl_vector_view column = gsl_matrix_column (A, 2); //obtener la columna j de la matriz A

    printf("Columna 2 de A: ");
    for(int i = 0; i < m; i++) //la columna tiene m elementos
    {
        printf("%g" " ", gsl_vector_get(&column.vector, i));
    }
    printf("\n");
    printf("----------\n");

    //--------------------------

    gsl_vector_view row = gsl_matrix_row(A, 1); //obtiene fila i de la matriz dada

    printf("Fila 1 de A: ");
    for(int i = 0; i < n; i++) //la fila tiene m elementos
    {
        printf("%g" " ", gsl_vector_get(&row.vector, i));
    }
    printf("\n");
    printf("----------\n");

    //--------------------------

    gsl_vector_view diag = gsl_matrix_diagonal(A); //obtiene la diagonal

    printf("Diagonal de A: ");
    for(int i = 0; i < n; i++) //la longitud de la diagonal es la menor dimension de la matriz
    {
        printf("%g" " ", gsl_vector_get(&diag.vector, i));
    }
    printf("\n");
    printf("----------\n");  

    //-------------------------

    gsl_matrix_memcpy(E, A); //Copia la matriz A en la matriz E
    gsl_matrix_swap_rows(E, 0, 4); //Intercambia la fila i con la fila j

    printf("Intercambio de fila 0 con la fila 4\n");
    printf("A' = \n");
    PrintMatrix(E);

    printf("----------\n");

    //-------------------------

    gsl_matrix_memcpy(E, A);
    gsl_matrix_swap_columns(E, 0, 2); //Intercambia la columna i con la columna j

    printf("Intercambio de columna 0 con la columna 2\n");
    printf("A' = \n");
    PrintMatrix(E);

    printf("----------\n");

    //---------------------------

    gsl_matrix_transpose_memcpy(D, A); //copia los elementos de A transpuesta en la matriz E
    printf("Matriz transpuesta:\n");
    printf("A^T' = \n");
    PrintMatrix(D);

    printf("----------\n");

    //---------------------------

    gsl_matrix_memcpy(E, A);
    gsl_matrix_add(E, B); // suma de matrices E + B, el resultado es guardado en la matriz E
    printf("Suma de matrices:\n");
    printf("A + B = \n");
    PrintMatrix(E);

    printf("----------\n");

    //---------------------------

    gsl_matrix_memcpy(E, A);
    gsl_matrix_sub(E, B); // resta de matrices E - B, el resultado es guardado en la matriz E
    printf("Resta de matrices:\n");
    printf("A - B = \n");
    PrintMatrix(E);

    printf("----------\n");

    //---------------------------

    gsl_matrix_memcpy(E, A);
    gsl_matrix_mul_elements(E, B); // multiplicacion de componentes por componentes de E y B, el resultado se guarda en E
    printf("Multiplicación componente por componente de matrices:\n");
    printf("A(i,j)*B(i,j) = \n");
    PrintMatrix(E);

    printf("----------\n");

    //---------------------------

    gsl_matrix_memcpy(E, A);
    gsl_matrix_div_elements(E, B); // division de componentes por componentes de E y B, el resultado se guarda en E
    printf("División componente por componente de matrices:\n");
    printf("A(i,j)/B(i,j) = \n");
    PrintMatrix(E);

    printf("----------\n");

    //---------------------------

    gsl_matrix_memcpy(E, A);
    gsl_matrix_scale(E, 3.9); // Multiplica los elementos de la matriz por el valor dado
    printf("Multiplicación de escalar por una matriz:\n");
    printf("3.9 A = \n");
    PrintMatrix(E);

    printf("----------\n");

    //---------------------------

    gsl_matrix_memcpy(E, A);
    gsl_matrix_add_constant(E, 3.9); // suma a los elementos de la matriz el valor dado
    printf("Suma de una matriz constante con una matriz:\n");
    printf("A + 3.9 = \n");
    PrintMatrix(E);

    printf("----------\n");

    //---------------------------
    printf("Máximo valor de una matriz:\n");
    printf("max(A) = " "%g\n", gsl_matrix_max(A)); //valor maximo de A
    printf("----------\n");

    //---------------------------
    printf("Mínimo valor de una matriz:\n");
    printf("min(A) = " "%g\n", gsl_matrix_min(A)); //valor minimo de A
    printf("----------\n");

    //---------------------------

    printf("¿C es nula? " "%d\n", gsl_matrix_isnull(C)); // 1 si, 0 no
    printf("----------\n");

    //---------------------------

    printf("¿A es estrictamente positiva? " "%d\n", gsl_matrix_ispos(A)); // 1 si, 0 no
    printf("----------\n");

    //---------------------------

    printf("¿B es estrictamente negativa? " "%d\n", gsl_matrix_isneg(B)); // 1 si, 0 no
    printf("----------\n");

    //---------------------------

    printf("¿D es no negativa? " "%d\n", gsl_matrix_isnonneg(D)); // 1 si, 0 no
    printf("----------\n");

    //---------------------------

    printf("¿A = B? " "%d\n", gsl_matrix_equal(A,B)); // 1 si, 0 no
    printf("----------\n");

    //---------------------------
    printf("Norma de una matriz:\n");
    printf("||A||_1 = " "%g\n", gsl_matrix_norm1(A)); // 1-norma de A
    printf("----------\n");

    gsl_matrix_free(B);
    gsl_matrix_free(C);
    gsl_matrix_free(D);
    gsl_matrix_free(E);

return 0;
}
