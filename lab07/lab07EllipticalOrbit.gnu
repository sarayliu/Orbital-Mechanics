#
# Sara Liu, 23 October 2019
#
# gnuplot lab07EllipticalOrbit.gnu
#
set terminal png
set output "lab07EllipticalOrbit.png"
#
set title "Elliptical Orbit Plot"
set xlabel "x, m"
set ylabel "y, m"
plot "orbitElliptical.txt" u 3:4 w l notitle
#
# end of file
#