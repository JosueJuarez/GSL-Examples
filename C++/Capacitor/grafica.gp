set terminal png
set output 'grafica.png'
set title "Dipolo eléctrico"

set key autotitle columnhead
set datafile separator ","

set yrange[-10:10]
set xrange[-10:10]
set palette rgb 33,13,10

set arrow from 1,2 to 1,-2 nohead lw 3 lc rgb "red"
set arrow from -1,2 to -1,-2 nohead lw 3 lc rgb "blue"
plot "./build/data.csv" using 1:2:($3/$5):($4/$5):5 with vectors head size 0.08,20,60 lc palette notitle


set terminal wxt persist
set output
replot