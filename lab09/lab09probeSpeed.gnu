#
# Sara Liu, 18 December 2019
#
# gnuplot lab09probeSpeed.gnu
#
set terminal png
set output "lab09probeSpeed.png"
#
set title "Speed of Probe over Time"
set xlabel "time, s"
set ylabel "speed, m/s"
plot "hyperbolicProbe.txt" u 2:7 w l notitle
#
# end of file
#