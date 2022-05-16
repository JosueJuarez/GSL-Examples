set terminal png
set output 'grafica.png'
set title "Regresión Lineal (ecuación maestra)"


set key autotitle columnhead
set datafile separator ","

f(x) = 1.10055 + 0.391512*x + 1.21488*x**2
plot "data.csv", f(x)

set terminal wxt persist
set output
replot