#!/bin/bash
for i in {1..9..1}
do
	echo i is $i
	filestring1="http://vis.cs.ucdavis.edu/data/5Jets/Energy/ns_000"$i"_e.dat"
 wget $filestring1 
	filestring2="http://vis.cs.ucdavis.edu/data/5Jets/Density/ns_000"$i"_r.dat"
 wget $filestring2 
done

for i in {10..20..1}
do
	echo i is $i
	filestring1="http://vis.cs.ucdavis.edu/data/5Jets/Energy/ns_00"$i"_e.dat"
 wget $filestring1 
	filestring2="http://vis.cs.ucdavis.edu/data/5Jets/Density/ns_00"$i"_r.dat"
 wget $filestring2 
done
