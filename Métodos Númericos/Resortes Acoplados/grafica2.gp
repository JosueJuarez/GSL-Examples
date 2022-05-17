set terminal png
set output 'grafica2.png'
set title "Energía"


set key autotitle columnhead
set datafile separator ","

plot "./build/data.csv" using 1:4 with lines

set terminal wxt persist
set output
replot