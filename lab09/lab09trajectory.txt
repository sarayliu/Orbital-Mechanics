#
# Sara Liu, 11 December 2019
#
# gnuplot lab09trajectory.gnu
#
set terminal png
set output "lab09trajectory.png"
#
set title "Hyperbolic Trajectory"
set xlabel "x, m"
set ylabel "y, m"
# set xrange[-4*10**8:4*10**8]
# set yrange[-4*10**8:4*10**8]
plot "hyperbolicProbe.txt" u 3:4 w l notitle, "hyperbolicProbe.txt" u 5:6 w l notitle
#
# end of file
#