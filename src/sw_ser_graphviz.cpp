#include <fstream>
#include <iostream>

#include <sw_ser_graphviz.hpp>


using namespace std;


bool SerializerGraphviz::serialize (string filename, SoftwareGenerator* gen)
{
	ofstream file;
	file.open(filename.c_str());

	file<<"digraph unix {"<<endl;
	file<<"\tsize=\"60,60\";"<<endl;

	for (SoftwareGenerator::Iterator it = gen->begin(); it!=gen->end(); it++) {
		if (dynamic_cast<t_real_task*>((*it)))
			file<<"\tnode [shape=ellipse];"<<endl;
		else
			file<<"\tnode [shape=box];"<<endl;
		file<<"\t\""<<(*it)->getName();
		file<<"\" [fillcolor = white, style=filled];"<<endl;

		file<<"\t"<<(*it)->getName()<<" -> "<<(*it)->getName()<<"_data ";
		file<<"[style=dotted, arrowhead=odot, arrowsize=1];"<<endl;
		file<<"\t"<<(*it)->getName()<<"_data [shape=plaintext,label=\"(";
		file<<(*it)->getWcet()<<" ";
		file<<")\"];"<<endl;
		file<<"\t{rank=same; "<<(*it)->getName()<<";";
		file<<(*it)->getName()<<"_data};"<<endl;
	}

	for (SoftwareGenerator::Iterator it = gen->begin(); it!=gen->end(); it++) {
		t_task* task = *it;
		for (t_task::DependencyIterator i = task->begin(); i!=task->end(); i++){
			file<<"\t\""<<(*i)->getPre()->getName()<<"\" -> \"";
			file<<(*i)->getPost()->getName()<<"\"";
			file<<"[label=\""<<(*i)->getCost()<<"\"];"<<endl;
		}
	}

	file<<"}"<<endl;

	file.close();

	return true;
}

