set terminal png
set output 'grafica.png'
set title "Dipolo eléctrico"

set key autotitle columnhead
set datafile separator ","

set yrange[-10:10]
set xrange[-10:10]
set label "-q" at -1,0 center
set label "+q" at  1,0 center
set palette rgb 33,13,10

plot "./build/data.csv" using 1:2:($3/$5):($4/$5):5 with vectors head size 0.08,20,60 lc palette notitle

set terminal wxt persist
set output
replot