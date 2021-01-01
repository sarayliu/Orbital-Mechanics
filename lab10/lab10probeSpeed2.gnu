#
# Sara Liu, 17 January 2020
#
# gnuplot lab10probeSpeed2.gnu
#
set terminal png
set output "lab10probeSpeed2.png"
#
set title "Speed of Probe 2 over Time"
set xlabel "time, s"
set ylabel "speed, m/s"
plot "hyperbolicProbeMPI2.txt" u 2:7 w l notitle
#
# end of file
#