set terminal png
set output 'grafica.png'
set title "Caminata aleatoria"
plot "./build/data.txt" with lines

set terminal wxt persist
set output
replot