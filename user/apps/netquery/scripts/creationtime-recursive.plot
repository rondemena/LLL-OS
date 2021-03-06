set terminal postscript color

latency(x)=x
latency3way(x)=3 * x

set title "Flow creation simulation, time to completion"

set xlabel "One-way propagation time (ms)"
set ylabel "Completion time (ms)"
plot 'recursive-O0.dat' using 4:3 title "Recursive, Opt level 0" with points,\
	'recursive-O1.dat' using 4:3 title "Recursive, Opt level 1"  with points,\
	latency(x) title "One-way propagation time",\
	latency3way(x) title "3 x propagation time (3-way handshake)"

pause -1
