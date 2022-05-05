Ejemplo de https://www.gnu.org/software/gsl/doc/latex/gsl-ref.pdf

Las siguientes lineas son para compilar:

		gcc -Wall -I/usr/local/include -c Ejemplo1.c
		gcc -L/usr/local/lib Ejemplo1.o -lgsl -lgslcblas -lm
		LD_LIBRARY_PATH=/usr/local/lib
		export LD_LIBRARY_PATH
		./a.out