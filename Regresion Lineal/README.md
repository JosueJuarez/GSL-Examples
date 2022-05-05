Ejemplo modificado de: https://www.gnu.org/software/gsl/doc/latex/gsl-ref.pdf

Regresión lineal usando datos de un archivo "data.csv" que contiene datos generados aleatoriamente de una función exponencial con ruido.

Realiza un ajuste de acuerdo al modelo $Y = c_{0} + c_{1}*X + c_{2}*X^2$

La salida del programa es la siguiente:

        Read 50 values.
        Read 50 values.
        Read 50 values.
        # best fit: Y = 1.06019 + 0.582337 X + 1.0868 X^2
        # covariance matrix:
        [ +2.36115e-03, -7.51085e-03, +4.38954e-03 
         -7.51085e-03, +3.94092e-02, -2.70459e-02 
         +4.38954e-03, -2.70459e-02, +2.09293e-02 ]
        # chisq = 52.3223


![Regresión Lineal Simple](./grafica.png)

# Creditos

 La lectura del archivo .csv es mediante el archivo tipo header "rapidcsv.h"; https://github.com/d99kris/rapidcsv