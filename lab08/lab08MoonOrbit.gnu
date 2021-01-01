#
# Sara Liu, 6 November 2019
#
# gnuplot lab08MoonOrbit.gnu
#
set terminal png
set output "lab08MoonOrbit.png"
#
set title "Moon Orbit Plot"
set xlabel "x, m"
set ylabel "y, m"
plot "orbitMoon.txt" u 3:4 w l notitle
#
# end of file
#