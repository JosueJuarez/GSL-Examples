set terminal png
set output 'grafica2.png'
set title "Comparación"


f(x) = 1.10055 + 0.391512*x + 1.21488*x**2
g(x) = 1.06019 + 0.582337*x + 1.0868*x**2
plot [0:2] f(x) title "Ecuación maestra", g(x) title "Regresión Lineal"

set terminal wxt persist
set output
replot