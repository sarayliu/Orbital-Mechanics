#
# Sara Liu, 17 January 2020
#
# gnuplot lab10trajectory1.gnu
#
set terminal png
set output "lab10trajectory1.png"
#
set title "Hyperbolic Trajectory 1"
set xlabel "x, m"
set ylabel "y, m"
set xrange[-4*10**8:4*10**8]
set yrange[-4*10**8:4*10**8]
plot "hyperbolicProbeMPI1.txt" u 3:4 w l notitle, "hyperbolicProbeMPI1.txt" u 5:6 w l notitle
#
# end of file
#