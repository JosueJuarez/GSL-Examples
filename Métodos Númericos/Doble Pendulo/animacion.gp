set term gif animate delay 30 size 400, 400
set output "animacion.gif"

set key autotitle columnhead
set datafile separator ","

set key center
set label right
set yrange[-3:3]
set xrange[-3:3]

x1(x) = sin(x)
y1(x) = -cos(x)
x2(x,y) = x1(x) + sin(y)
y2(x,y) = y1(x) - cos(y)

do for [n=1:100] {
	set title sprintf("t = %g", n*0.15)

    plot "./build/data.csv" every ::n::n using ( x1($2) ):( y1($2) ) notitle with points pointtype 7 pointsize 3,\
    "./build/data.csv" every ::n::n using ( x2($2,$3) ):( y2($2,$3) ) notitle with points pointtype 7 pointsize 3,\
    "./build/data.csv" every ::n::n using 0:0:( x1($2) ):( y1($2) ) notitle with vectors nohead,\
    "./build/data.csv" every ::n::n using ( x1($2) ):( y1($2) ):( sin($3) ):( -cos($3) ) notitle with vectors nohead


} 
