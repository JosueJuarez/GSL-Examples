set terminal png
set output 'grafica.png'
set title "Regresión Lineal"


set key autotitle columnhead
set datafile separator ","

f(x) = 1.06019 + 0.582337*x + 1.0868*x**2
plot "data.csv", f(x)

set terminal wxt persist
set output
replot