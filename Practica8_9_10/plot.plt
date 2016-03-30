set terminal png size 500 500 enhanced font "Helvetica,20"
set output 'plot.png'
set title "A simple plot of sin(x) vs x"
set xlabel "x"
set ylabel "y"
plot "./data.dat" using 1:2 title "Grafica"
