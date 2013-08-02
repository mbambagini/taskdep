#! /bin/sh


################################## PARAMETERS ##################################

########## GENERATOR
#0: CODE-STYLE GENERATOR
#1: DATA FLOW GENERATOR
GEN=0

########## WCET: WORST-CASE EXECUTION TIME
maxWcet=5000
minWcet=1000

########## AMOUNT OF EXCHANGED DATA
maxData=200
minData=100

########## TASK NUMBER
tasks=20

########## IF GEN==0
#prob=0.0 #fully sequential
#prob=1.0 #fully parallel
prob=0.5
##########

########## USEFUL IF GEN==1
deps=10
distance=5
##########


################################## PROCESSING ##################################

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

