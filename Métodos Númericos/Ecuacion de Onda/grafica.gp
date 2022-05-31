set terminal png
set output 'grafica.png'
set title "Ecuación de Onda"

set key autotitle columnhead
set datafile separator ","

set yrange[-1.5:1.5]
set xrange[0:1]


plot "./build/data.csv" using 1:2 with lines,\
	"./build/data.csv" using 1:3 with lines

set terminal wxt persist
set output
replot