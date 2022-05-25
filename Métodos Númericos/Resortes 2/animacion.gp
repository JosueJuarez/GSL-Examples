set term gif animate delay 30 size 400, 400
set output "animacion.gif"

set key autotitle columnhead
set datafile separator ","

set key center
set yrange[0:1]
set xrange[-2:10]

do for [n=1:100] {
	set title sprintf("t = %g", n*0.15)

    plot "./build/data.csv" every ::n::n using 2:(0) with points pointtype 7 pointsize 3,\
    "./build/data.csv" every ::n::n using ( $3+4.0 ):(0) with points pointtype 7 pointsize 3,\
    "./build/data.csv" every ::n::n using ( $4+8.0 ):(0) with points pointtype 7 pointsize 3
} 
