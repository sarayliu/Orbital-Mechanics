#
# Sara Liu, 25 October 2019
#
# gnuplot lab07HyperbolicDistance.gnu
#
set terminal png
set output "lab07HyperbolicDistance.png"
#
set title "Hyperbolic Distance Plot"
set xlabel "time, s"
set ylabel "distance, m"
plot "orbitHyperbolic.txt" u 2:5 w l notitle
#
# end of file
#