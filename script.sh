#! /bin/sh


#### PARAMETERS

#GENERATOR
#0: SOFTWARE LIKE GENERATOR
#1: DATA FLOW GENERATOR
GEN=0

#WCET
maxWcet=5000
minWcet=1000

#EXCHANGED DATA
maxData=200
minData=100

#GENERATION
tasks=30
deps=15
distance=5
#prob=0.0 #fully sequential
#prob=1.0 #fully parallel
prob=0.5


#### ARGUMENT
if [ $# -lt 1 ];
then
	echo "The parameter is missing"
	echo "$0 <project name>"
	exit
fi


#### EXECUTING
./software	--binaryFile=$1.bin --plainTextFile=$1.txt --graphvizFile=$1.dot \
			--taskGenerator $GEN --nOfTasks $tasks --nOfDependencies $deps \
			--dependencyDistance $distance --probSeqPar $prob \
			--maxWcet $maxWcet --minWcet $minWcet \
			--maxExchangedData $maxData --minExchangedData $minData 

####PRINTING
dot $1.dot -o $1.png -Tpng

