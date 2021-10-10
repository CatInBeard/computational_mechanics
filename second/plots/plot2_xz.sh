#!/usr/bin/gnuplot -persist
set key autotitle columnheader
set grid
set xlabel 'x'; set ylabel 'U';
set xyplane relative 0
set dgrid3d 7,5
set hidden3d
set view 30,45
set term png
set output "img/5.png"

plot "data/data2_1_xz.csv" with lines lt rgb "#FF0000", "data/data2_2_xz.csv" with lines lt rgb "#00FF00","data/data2_3_xz.csv" with lines lt rgb "#0000FF"