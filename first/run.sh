#!/bin/bash
mkdir -p output
mkdir -p data
mkdir -p img
make
./output/build
./plots/plot1.sh
./plots/plot2.sh
./plots/plot_xz.sh
./plots/plot1_xz.sh
./plots/plot2_xz.sh
pdflatex report.tex
rm report.log
rm report.toc
rm report.aux
okular report.pdf
