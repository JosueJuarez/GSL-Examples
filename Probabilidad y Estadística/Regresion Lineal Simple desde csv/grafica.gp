set terminal png
set output 'grafica.png'
set title "Regresión Lineal Simple"


set key autotitle columnhead
set datafile separator ","

f(x) = -4.99858 + 2.02721*x
plot "data.csv", f(x)

set terminal wxt persist
set output
replot