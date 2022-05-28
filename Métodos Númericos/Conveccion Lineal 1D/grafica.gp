set terminal png
set output 'grafica.png'
set title "Convección Lineal 1D"

set key autotitle columnhead
set datafile separator ","

set yrange[0:1.3]
set xrange[0:2]


plot "./build/data.csv" using 1:2 with lines,\
	"./build/data.csv" using 1:3 with lines

set terminal wxt persist
set output
replot