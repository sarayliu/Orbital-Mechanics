#
# Sara Liu, 25 October 2019
#
# gnuplot lab07HyperbolicOrbit.gnu
#
set terminal png
set output "lab07HyperbolicOrbit.png"
#
set title "Hyperbolic Orbit Plot"
set xlabel "x, m"
set ylabel "y, m"
plot "orbitHyperbolic.txt" u 3:4 w l notitle
#
# end of file
#