#include <sw_gen_data.hpp>

#include <algorithm>
#include <limits>
#include <iostream>
#include <sstream>

#include <math.h>

using namespace std;




/******************************** DEPENDENCIES ********************************/

void DataFlowSoftwareGenerator::generate_dependencies ()
{
	int diff = getMaxExchangedData()-getMinExchangedData();
	int i = 0;
	while (i<getDependencyNumber()) {
		int from = getRnder()->randInt(getTaskNumber()-1);
		int to = from + getRnder()->randInt(getMaxDependencyDistance())+1;
		if (to>=getTaskNumber())
			to = getTaskNumber()-1;
		bool found = false;
		for (list<t_dependency*>::iterator it = dependencies.begin();
												   it!=dependencies.end(); it++)
			if ((*it)->getPost()==tasks[to] && (*it)->getPre()==tasks[from]) {
				found = true;
				break;
			}
		if (found)
			continue;
		t_dependency* dep = new t_dependency();
		dep->setPost(tasks[to]);
		dep->setPre(tasks[from]);
		dep->setCost (getRnder()->randInt(diff)+getMinExchangedData());
		tasks[from]->addDepOut(dep);
		tasks[to]->addDepIn(dep);
		dependencies.push_back(dep);
		i++;
	}
}


/************************************ TASK ************************************/

void DataFlowSoftwareGenerator::generate_tasks ()
{
	tasks.resize(getTaskNumber());
	int diff = getMaxWcet()-getMinWcet();
	for (int i=  0; i<getTaskNumber(); i++) {
		t_task* task = new t_real_task();
		task->setID(i);
		task->setWcet(getRnder()->randInt(diff)+getMinWcet());
		tasks[i] = task;
	}
}

