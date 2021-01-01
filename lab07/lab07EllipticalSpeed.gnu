#
# Sara Liu, 25 October 2019
#
# gnuplot lab07EllipticalSpeed.gnu
#
set terminal png
set output "lab07EllipticalSpeed.png"
#
set title "Elliptical Speed Plot"
set xlabel "time, s"
set ylabel "speed, m/s"
plot "orbitElliptical.txt" u 2:6 w l notitle
#
# end of file
#