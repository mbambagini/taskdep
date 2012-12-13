#include <fstream>
#include <iostream>

#include <sw_ser_protobuf.hpp>
#include <taskgraph.pb.h>


using namespace std;
using namespace TaskGraph;


bool SerializerProtobuf::serialize (string filename, SoftwareGenerator* gen)
{
	Graph graph;

	graph.set_maxwcet(gen->getMaxWcet());
	graph.set_minwcet(gen->getMinWcet());
	graph.set_maxexchangeddata(gen->getMaxExchangedData());
	graph.set_minexchangeddata(gen->getMinExchangedData());

	SoftwareGenerator::Iterator it = gen->begin();
	for (int i=0; it!=gen->end(); it++, i++) {
		TaskGraph::Task *task = graph.add_tasks();
		task->set_id(i);
		task->set_name((*it)->getName());
		if (dynamic_cast<t_sync_task*>(*it))
			task->set_sync(1);
		task->set_wcet((*it)->getWcet());
	}

	for (it = gen->begin(); it!=gen->end(); it++) {
		t_task* task = *it;
		for (t_task::DependencyIterator i = task->begin(); i!=task->end(); i++){
			TaskGraph::Dependency *dep = graph.add_dependencies();
			dep->set_fromtask((*i)->getPre()->getName());
			dep->set_totask((*i)->getPost()->getName());
			dep->set_exchangeddata((*i)->getCost());
		}
	}

	fstream output(filename.c_str(), ios::out | ios::trunc | ios::binary);
	if (!graph.SerializeToOstream(&output)) {
		cerr << "Failed to serialize." << endl;
		return -1;
	}

	google::protobuf::ShutdownProtobufLibrary();

	return true;
}

