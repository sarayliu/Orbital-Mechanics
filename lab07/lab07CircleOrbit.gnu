#
# Sara Liu, 21 October 2019
#
# gnuplot lab07CircleOrbit.gnu
#
set terminal png
set output "lab07CircleOrbit.png"
#
set title "Circlular Orbit Plot"
set xlabel "x, m"
set ylabel "y, m"
plot "orbit.txt" u 3:4 w l notitle
#
# end of file
#