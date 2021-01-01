#
# Sara Liu, 23 October 2019
#
# gnuplot lab07CircleDistance.gnu
#
set terminal png
set output "lab07CircleDistance.png"
#
set title "Circlular Distance Plot"
set xlabel "time, s"
set ylabel "distance, m"
#
set yrange[0:14*10**6]
#
plot "orbit.txt" u 2:5 w l notitle
#
# end of file
#