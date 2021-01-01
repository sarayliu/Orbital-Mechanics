#
# Sara Liu, 17 January 2020
#
# gnuplot lab10dAM2.gnu
#
set terminal png
set output "lab10dAM2.png"
#
set title "Distance to Moon from Probe 2"
set xlabel "time, s"
set ylabel "distance, m"
plot "hyperbolicProbeMPI2.txt" u 2:8 w l notitle
#
# end of file
#