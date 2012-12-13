#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <randomizer.hpp>
#include <sw_gen.hpp>
#include <sw_gen_data.hpp>
#include <sw_gen_code.hpp>
#include <sw_ser_protobuf.hpp>
#include <sw_ser_graphviz.hpp>
#include <sw_ser_text.hpp>

#include <taskgraph.pb.h>
#include <gflags/gflags.h>


using namespace std;


/******************************************************************************
 * ARGUMENT DEFINITION
 ******************************************************************************/

//input files
DEFINE_string(binaryFile, "", "Binary file with the generated task graph");
DEFINE_string(plainTextFile, "", "Plain text with the generated task graph");
DEFINE_string(graphvizFile, "", "DOT file with the generated task graph");


//0: SOFTWARE LIKE GENERATOR
//1: DATA FLOW GENERATOR
DEFINE_int32(taskGenerator, 0, "Task generator to use: 0 (code-style), \
																1 (data flow)");

DEFINE_int32(maxWcet, 200, "Maximum Worst-Case Execution Time");
DEFINE_int32(minWcet, 100, "Minimum Worst-Case Execution Time");

DEFINE_int32(maxExchangedData, 2000, "Maximum amount of exchanged data");
DEFINE_int32(minExchangedData, 1000, "Minimum amount of exchanged data");

DEFINE_int32(nOfTasks, 15, "Number of tasks");
DEFINE_int32(nOfDependencies, 15, "Number of Dependencies");

//data-flow generator
DEFINE_int32(dependencyDistance, 5, "Maximum dependency distance");
//software like generator
DEFINE_double(probSeqPar, 0.5, "Ser/Par probability [0, 1]");


/******************************************************************************
 * MAIN FUNCTION
 ******************************************************************************/

int main (int argc, char* argv[])
{

	//parameter check
	google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_binaryFile.compare("")==0) {
		cerr<<"The output file parameter is mandatory"<<endl;
		return 1;
	}

	//instance creation
	Randomizer rnd;
	SoftwareGenerator *gen;
	switch (FLAGS_taskGenerator) {
	case 0:
		gen = new CodeStyleSoftwareGenerator();
		((CodeStyleSoftwareGenerator*)gen)->setProbability(FLAGS_probSeqPar);
		break;
	case 1:
		gen = new DataFlowSoftwareGenerator();
		((DataFlowSoftwareGenerator*)gen)->setDependencyNumber(
														 FLAGS_nOfDependencies);
		((DataFlowSoftwareGenerator*)gen)->setMaxDependencyDistance(
													  FLAGS_dependencyDistance);
		break;
	default:
		exit(0);
	}

	//configuration
	gen->setTaskNumber(FLAGS_nOfTasks);
	gen->setMaxWcet(FLAGS_maxWcet);
	gen->setMinWcet(FLAGS_minWcet);
	gen->setMaxExchangedData(FLAGS_maxExchangedData);
	gen->setMinExchangedData(FLAGS_minExchangedData);
	gen->setRnder(&rnd);

	//generation
	gen->generate();

	//serialization
	SerializerProtobuf ser;
	ser.serialize(FLAGS_binaryFile, gen);
	if (FLAGS_plainTextFile.compare("")!=0) {
		SerializerPlainText ser;
		ser.serialize(FLAGS_plainTextFile, gen);
	}
	if (FLAGS_graphvizFile.compare("")!=0) {
		SerializerGraphviz ser;
		ser.serialize(FLAGS_graphvizFile, gen);
	}

	delete gen;

	return 0;
}

