#!/bin/sh
################################################################################
# Bradford Smith (bsmith8)
# CS 492 Assignment 2 plot.sh
# 04/02/2016
# "I pledge my honor that I have abided by the Stevens Honor System."
################################################################################

# This is a script to automate running trials and creating graphs based on the
# results using gnuplot and ImageMagic

# Variables for filenames and trial results
TEMP="./gnuplot.in"
DATA1="../demand.dat"
DATA2="../prepaging.dat"
OUT1="../demand_graph.png"
OUT2="../prepaging_graph.png"
OUT3="../graph.png"
FIFO=""
LRU=""
CLOCK=""

# Fill $DATA with FIFO,LRU and Clock results using demand paging for page sizes
# 1, 2, 4, 8, and 16
echo -n > $DATA1
for i in 1 2 4 8 16
do
    FIFO="$(./VMsimulator ../plist ../ptrace $i FIFO - | sed 's/[^0-9]*//g')"
    LRU="$(./VMsimulator ../plist ../ptrace $i LRU - | sed 's/[^0-9]*//g')"
    CLOCK="$(./VMsimulator ../plist ../ptrace $i Clock - | sed 's/[^0-9]*//g')"
    echo "${i} ${FIFO} ${LRU} ${CLOCK}" >> $DATA1
done

# Create temporary gnuplot input file for demand paging plot
echo -n > $TEMP
echo "set term png" >> $TEMP
echo "set xlabel \"Page Size\"" >> $TEMP
echo "set ylabel \"Page Faults (in Thousands)\"" >> $TEMP
echo "set xtics (1, 2, 4, 8, 16)" >> $TEMP
echo "set key reverse Left outside" >> $TEMP
echo "set grid" >> $TEMP
echo "set style data linespoints" >> $TEMP
echo "set output \"${OUT1}\"" >> $TEMP
echo "set title \"Demand Paging\"" >> $TEMP
echo "plot \"${DATA1}\" using 1:(\$2/1000) title \"FIFO\", \
\"\" using 1:(\$3/1000) title \"LRU\", \
\"\" using 1:(\$4/1000) title \"Clock\"" >> $TEMP

# plot the demand paging graph
gnuplot $TEMP

# Fill $DATA with FIFO,LRU and Clock results using pre-paging for page sizes
# 1, 2, 4, 8, and 16
echo -n > $DATA2
for i in 1 2 4 8 16
do
    FIFO="$(./VMsimulator ../plist ../ptrace $i FIFO + | sed 's/[^0-9]*//g')"
    LRU="$(./VMsimulator ../plist ../ptrace $i LRU + | sed 's/[^0-9]*//g')"
    CLOCK="$(./VMsimulator ../plist ../ptrace $i Clock + | sed 's/[^0-9]*//g')"
    echo "${i} ${FIFO} ${LRU} ${CLOCK}" >> $DATA2
done

# Create temporary gnuplot input file for pre-paging plot
echo -n > $TEMP
echo "set term png" >> $TEMP
echo "set xlabel \"Page Size\"" >> $TEMP
echo "set ylabel \"Page Faults (in Thousands)\"" >> $TEMP
echo "set xtics (1, 2, 4, 8, 16)" >> $TEMP
echo "set key reverse Left outside" >> $TEMP
echo "set grid" >> $TEMP
echo "set style data linespoints" >> $TEMP
echo "set output \"${OUT2}\"" >> $TEMP
echo "set title \"Pre-Paging\"" >> $TEMP
echo "plot \"${DATA2}\" using 1:(\$2/1000) title \"FIFO\", \
\"\" using 1:(\$3/1000) title \"LRU\", \
\"\" using 1:(\$4/1000) title \"Clock\"" >> $TEMP

# plot the pre-paging graph
gnuplot $TEMP

# merge the two plots to one png side by side using ImageMagic
convert $OUT1 $OUT2 +append $OUT3

# cleanup
rm $OUT1
rm $OUT2
rm $TEMP

