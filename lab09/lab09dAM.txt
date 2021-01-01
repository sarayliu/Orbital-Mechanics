#
# Sara Liu, 18 December 2019
#
# gnuplot lab09dAM.gnu
#
set terminal png
set output "lab09dAM.png"
#
set title "Distance to Moon from Probe"
set xlabel "time, s"
set ylabel "distance, m"
plot "hyperbolicProbe.txt" u 2:8 w l notitle
#
# end of file
#