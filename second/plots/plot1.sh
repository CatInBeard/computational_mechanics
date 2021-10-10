#!/usr/bin/gnuplot -persist
set key autotitle columnheader
set grid
set xlabel 'x'; set ylabel 't'; set zlabel 'U'
set xyplane relative 0
set dgrid3d 11,11
set hidden3d
set view 120,45
set term png
set output "img/1.png"
set palette rgbformulae 30,31,32
splot 'data/data1_xyz.csv' every :1 w pm3d