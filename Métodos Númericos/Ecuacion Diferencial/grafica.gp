set terminal png
set output 'grafica.png'
set title "Van der Pol oscillator"


set key autotitle columnhead
set datafile separator ","

plot "./build/data.csv" with lines

set terminal wxt persist
set output
replot