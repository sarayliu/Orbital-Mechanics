#
# Sara Liu, 25 October 2019
#
# gnuplot lab07HyperbolicSpeed.gnu
#
set terminal png
set output "lab07HyperbolicSpeed.png"
#
set title "Hyperbolic Speed Plot"
set xlabel "time, s"
set ylabel "speed, m/s"
plot "orbitHyperbolic.txt" u 2:6 w l notitle
#
# end of file
#