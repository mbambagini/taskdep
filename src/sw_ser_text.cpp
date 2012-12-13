#include <fstream>
#include <iostream>
#include <iomanip>

#include <sw_ser_text.hpp>
#include <sw_gen.hpp>


using namespace std;

bool SerializerPlainText::serialize (string filename, SoftwareGenerator* gen)
{
	ofstream file;
	file.open(filename.c_str());

	file<<"#Tasks:\t\t"<<gen->getTaskNumber()<<endl;
	file<<"#Deps: \t\t"<<gen->getDependencyNumber()<<endl<<endl;

	file<<"Max wcet: \t\t\t"<<gen->getMaxWcet()<<endl;
	file<<"Min wcet: \t\t\t"<<gen->getMinWcet()<<endl;
	file<<"Max exchanged data: \t\t\t"<<gen->getMaxExchangedData()<<endl;
	file<<"Min exchanged data: \t\t\t"<<gen->getMinExchangedData()<<endl;
	file<<endl;

	file<<"Tasks:"<<endl;
	file<<setw(20)<<"NAME"<<setw(10)<<"SYNC?"<<setw(10)<<"WCET";
	file<<endl;
	for (SoftwareGenerator::Iterator it = gen->begin(); it!=gen->end(); it++) {
		file<<setw(20)<<(*it)->getName();
		if (dynamic_cast<t_sync_task*>(*it))
			file<<setw(10)<<"Y";
		else
			file<<setw(10)<<"N";
		file<<setw(10)<<(*it)->getWcet()<<endl;
	}
	file<<endl;

	file<<"Dependencies:"<<endl;
	file<<setw(10)<<"FROM"<<setw(10)<<"TO"<<setw(20)<<"DATA"<<endl;
	for (SoftwareGenerator::Iterator it = gen->begin(); it!=gen->end(); it++) {
		t_task* task = *it;
		for (t_task::DependencyIterator i = task->begin(); i!=task->end(); i++){
			file<<setw(10)<<(*i)->getPre()->getName();
			file<<setw(10)<<(*i)->getPost()->getName();
			file<<setw(20)<<(*i)->getCost()<<endl;
		}
	}

	file.close();

	return true;
}

