set terminal png
set output 'grafica.png'
set title "sen(x)"
plot "./build/data.txt"

set terminal wxt persist
set output
replot