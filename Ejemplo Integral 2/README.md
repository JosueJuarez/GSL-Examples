Ejemplo obtenido de  https://www.gnu.org/software/gsl/doc/latex/gsl-ref.pdf

Calcula númericamente la integral
$I = \int_{\infty}^{\infty} \exp(-x^2)*(x^m + 1)dx$
El valor exacto de la integral depende del número $m$
$I = \sqrt{\pi} + \Gamma((m+1)/2)$, si $m$ es par, $\Gamma(x)$ es la función Gamma
$I = \sqrt{\pi}$, si $m$ es impar

La salida del programa es la siguiente:

		m = 10
		intervals = 6
		result =  54.115231635459096537
		exact result =  54.115231635459025483
		actual error =  0.000000000000071054
