#
# Sara Liu, 17 January 2020
#
# gnuplot lab10trajectory2.gnu
#
set terminal png
set output "lab10trajectory2.png"
#
set title "Hyperbolic Trajectory 2"
set xlabel "x, m"
set ylabel "y, m"
# set xrange[-4*10**8:4*10**8]
# set yrange[-4*10**8:4*10**8]
plot "hyperbolicProbeMPI2.txt" u 3:4 w l notitle, "hyperbolicProbeMPI2.txt" u 5:6 w l notitle
#
# end of file
#