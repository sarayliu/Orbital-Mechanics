#
# Sara Liu, 25 October 2019
#
# gnuplot lab07EllipticalDistance.gnu
#
set terminal png
set output "lab07EllipticalDistance.png"
#
set title "Elliptical Distance Plot"
set xlabel "time, s"
set ylabel "distance, m"
plot "orbitElliptical.txt" u 2:5 w l notitle
#
# end of file
#