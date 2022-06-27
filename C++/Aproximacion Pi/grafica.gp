set terminal png
set output 'grafica.png'
set title "Aproximaciones de Pi"

set key autotitle columnhead
set datafile separator ","

plot "./build/data.csv" using 1:2 with lines

set terminal wxt persist
set output
replot