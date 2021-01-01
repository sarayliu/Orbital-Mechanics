#
# Sara Liu, 18 November 2019
#
# gnuplot lab08ApolloSpeed.gnu
#
set terminal png
set output "lab08ApolloSpeed.png"
#
set title "Speed of Apollo over Time"
set xlabel "time, s"
set ylabel "speed, m/s"
set xrange[0:300000]
plot "freeReturn.txt" u 2:8 w l notitle
#
# end of file
#