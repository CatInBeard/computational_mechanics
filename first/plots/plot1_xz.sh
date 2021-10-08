#!/usr/bin/gnuplot -persist
set key autotitle columnheader
set grid
set xlabel 'x'; set ylabel 'z';
set xyplane relative 0
set dgrid3d 7,5
set hidden3d
set view 30,45
set term png
set output "img/4.png"

plot "data/data1_1_xz.csv" with lines lt rgb "#FF0000", "data/data1_2_xz.csv" with lines lt rgb "#00FF00","data/data1_3_xz.csv" with lines lt rgb "#0000FF"