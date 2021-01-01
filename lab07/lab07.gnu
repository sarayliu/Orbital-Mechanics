#
# Torbert, 2 November 2012
#
# gnuplot demo1.gnu
#
set terminal png
set output "demo1.png"
plot "demo1.txt" u 1:2 w l notitle
#
# end of file
#