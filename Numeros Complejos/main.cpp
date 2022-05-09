#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

int main()
{
	gsl_complex x, y, z; //definir dos números complejos

	//x = 4 + 2i
	GSL_REAL(x) = 4; //parte real
	GSL_IMAG(x) = 2; //parte imaginaria
	//y = 3 + i
	GSL_SET_COMPLEX(&y, 3, 1); //otra forma de definirlo
	//z = 5*exp(i*0)
	z = gsl_complex_polar(5, M_PI/2); //Definir el número en forma polar z=r*exp(i*theta)

	printf ("x = % .18f + % .18f i \n", GSL_REAL(x), GSL_IMAG(x));
	printf ("y = % .18f + % .18f i \n", GSL_REAL(y), GSL_IMAG(y));
	printf ("z = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));

	printf("arg(x) = % .18f\n", gsl_complex_arg(x)); //argumento de x
	printf("|x| = % .18f\n", gsl_complex_abs(x)); //Valor absoluto de x
	printf("arg(x) = % .18f\n", gsl_complex_logabs(x)); //logaritmo de |x|

	z = gsl_complex_add(x,y); // x+y
	printf ("x + y = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_sub(x,y); // x-y
	printf ("x - y = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_mul(x,y); // x*y
	printf ("x*y = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_div(x,y); // x/y
	printf ("x*y = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_conjugate(x); // *x
	printf ("*x = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_inverse(x); // 1/x
	printf ("1/x = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_sqrt(x); //sqrt(z)
	printf ("sqrt(x) = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_pow(x, y); // x^y
	printf ("x^y = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_exp(x); // exp(x)
	printf ("exp(x) = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_log(x); //log(x)
	printf ("log(x) = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_sin(x); //sen(x)
	printf ("sen(x) = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_arccos(x); //arcos(x)
	printf ("arcos(x) = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_tanh(x); //tanh(x)
	printf ("tanh(x) = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));
	z = gsl_complex_arcsech(x); //arcsech(x)
	printf ("arcsech(x) = % .18f + % .18f i \n", GSL_REAL(z), GSL_IMAG(z));

return 0;
}