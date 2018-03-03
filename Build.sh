#! /bin/bash
echo "Processing the GRAHAM Vs Parallel Divide and Conquer methods"
echo "____________________________________________________________"
for i in 0 3 
do
       	echo "----------------------------------------------------------------------------------"
	echo "************************* Compiling with Optimization -O$i ************************"
	echo "----------------------------------------------------------------------------------"
	g++ -std=c++11 -D GRAHAM -D FORK -Wall -Werror -pedantic -O$i -o WithFork_O${i}.out *.cc
	g++ -std=c++11 -D GRAHAM -Wall -Werror -pedantic -O$i -o WithoutFork_O${i}.out *.cc
done	
