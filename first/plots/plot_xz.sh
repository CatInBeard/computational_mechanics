#!/usr/bin/gnuplot -persist
set key autotitle columnheader
set grid
set xlabel 'x'; set ylabel 'T';
set xyplane relative 0
set dgrid3d 7,5
set hidden3d
set view 30,45
set term png
set output "img/3.png"
set multiplot layout 1,3

plot "data/data1_1_xz.csv" with lines lt rgb "#00FF00" title "explicit", "data/data2_1_xz.csv" with lines lt rgb "#FF0000" title "implicit"

plot "data/data1_2_xz.csv" with lines lt rgb "#00FF00" title "explicit", "data/data2_2_xz.csv" with lines lt rgb "#FF0000" title "implicit"

plot "data/data1_3_xz.csv" with lines lt rgb "#00FF00" title "explicit", "data/data2_3_xz.csv" with lines lt rgb "#FF0000" title "implicit"