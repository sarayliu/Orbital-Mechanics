#
# Sara Liu, 15 November 2019
#
# gnuplot lab08FreeReturn.gnu
#
set terminal png
set output "lab08FreeReturn.png"
#
set title "Free Return Trajectory"
set xlabel "x, m"
set ylabel "y, m"
set xrange[-4*10**8:4*10**8]
set yrange[-4*10**8:4*10**8]
plot "freeReturn.txt" u 3:4 w l notitle, "freeReturn.txt" u 6:7 w l notitle
#
# end of file
#