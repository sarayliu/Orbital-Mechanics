#
# Sara Liu, 23 October 2019
#
# gnuplot lab07CircleSpeed.gnu
#
set terminal png
set output "lab07CircleSpeed.png"
#
set title "Circlular Speed Plot"
set xlabel "time, s"
set ylabel "speed, m/s"
#
set yrange[0:15345]
#
plot "orbit.txt" u 2:6 w l notitle
#
# end of file
#