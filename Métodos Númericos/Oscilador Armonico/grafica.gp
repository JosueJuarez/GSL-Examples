set terminal png
set output 'grafica.png'
set title "Oscilador Armónico"


set key autotitle columnhead
set datafile separator ","

plot "./build/data.csv" using 1:2 with lines

set terminal wxt persist
set output
replot