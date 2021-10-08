#!/usr/bin/gnuplot -persist
set key autotitle columnheader
set grid
set xlabel 'x'; set ylabel 't'; set zlabel 'T'
set xyplane relative 0
set dgrid3d 7,5
set hidden3d
set view 30,45
set term png
set output "img/1.png"
splot 'data/data1_xyz.csv' w l  palette
