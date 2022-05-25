set terminal png
set output 'grafica.png'
set title "Resortes Acoplados"


set key autotitle columnhead
set datafile separator ","

plot "./build/data.csv" using 1:2 with lines, "./build/data.csv" using 1:3 with lines, "./build/data.csv" using 1:4 with lines

set terminal wxt persist
set output
replot