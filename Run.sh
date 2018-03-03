#!/bin/bash
points_file="/home/NETID/anada/U/CSS503_Assignment_1_2/points10000000.txt"
if [ ! -f "$points_file" ]
then
	    echo "$0: File '${points_file}' not found, will create one."
	    ./generate_data.py 10000000 > points10000000.txt
    fi
echo "Processing the GRAHAM Vs Parallel Divide and Conquer methods"
echo "____________________________________________________________"
for i in 0 3 
do
#	echo "----------------------------------------------------------------------------------"
#	echo "************************* Starting with Optimization -O$i ************************"
#	echo "----------------------------------------------------------------------------------"
#	g++ -std=c++11 -D GRAHAM -D FORK -Wall -Werror -pedantic -O$i -o WithFork_O${i}.out *.cc
#	g++ -std=c++11 -D GRAHAM -Wall -Werror -pedantic -O$i -o WithoutFork_O${i}.out *.cc
	for j in 1 2 4 8 16 
	do
		echo "###################Compiling using $j Processors#######################"
		echo "Testing without fork" 
		echo "--------------------"
		./WithoutFork_O${i}.out $j < points10000000.txt > results/output_O${i}_${j}_Processor_WithoutFORK.txt 
		while read -r line; do
			if [[ $line == *Graham*  ]] ;
			then
				file=/home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_WithoutFORK_Graham.txt; fi
				if [[ $line != @*  ]] ;
				then echo $line >> $file ; 
				elif [[ $line == *divide*  ]]
				then
					file=/home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_WithoutFORK_Divide_Conquer.txt; fi
				done < /home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_WithoutFORK.txt
				DIFF=$(diff /home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_WithoutFORK_Divide_Conquer.txt /home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_WithoutFORK_Graham.txt)
				if [ "$DIFF" == "" ] 
				then
					echo "Graham Scan and Divide and Conquer algortithm results match"
				else 
					echo "Graham scan and Divide and Conquer algorithms results don't match"
				fi
				echo "Testing with fork"
				echo "-----------------"
				./WithFork_O${i}.out $j < points10000000.txt > results/output_O${i}_${j}_Processor_FORK.txt
while read -r line; do
if [[ $line == *Graham*  ]] ;
then
	file=/home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_FORK_Graham.txt; fi
if [[ $line != @*  ]] ;
then echo $line >> $file ; 
elif [[ $line == *divide*  ]]
then
        file=/home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_FORK_Divide_Conquer.txt; fi
done < /home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_FORK.txt
DIFF=$(diff /home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_FORK_Divide_Conquer.txt /home/NETID/anada/U/CSS503_Assignment_1_2/results/output_O${i}_${j}_Processor_FORK_Graham.txt)
if [ "$DIFF" == "" ] 
then
	        echo "Graham Scan and Divide and Conquer algortithm results match"
	else 
		        echo "Graham scan and Divide and Conquer algorithms results don't match"
		fi
			done
		done
