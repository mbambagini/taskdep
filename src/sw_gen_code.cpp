#include <sw_gen_code.hpp>

#include <limits>
#include <iostream>
#include <sstream>
#include <math.h>


using namespace std;


/********************************** SOFTWARE **********************************/

void CodeStyleSoftwareGenerator::create_dependency (t_task* from, t_task* to)
{

	t_dependency* dep = new t_dependency();
	dep->setPost(to);
	dep->setPre(from);
	if (dynamic_cast<t_sync_task*>(to) || dynamic_cast<t_sync_task*>(from))
		dep->setCost (0);
	else {
		int diff = getMaxExchangedData()-getMinExchangedData();
		dep->setCost (getRnder()->randInt(diff)+getMinExchangedData());
	}

	from->addDepOut(dep);
	to->addDepIn(dep);
	depNumber++;
}

t_task* CodeStyleSoftwareGenerator::create_task (int id)
{
	t_task* task = new t_real_task();
	task->setID(id);
	task->setWcet(getRnder()->randInt(getMaxWcet()-getMinWcet())+getMinWcet());
	tasks.push_back(task);
	return task;
}

t_task* CodeStyleSoftwareGenerator::create_sync ()
{
	t_task* task = new t_sync_task();
	tasks.push_back(task);
	return task;
}

void CodeStyleSoftwareGenerator::generate_tasks_internal (t_task* fork, 
												  t_task* join, list<int> lista)
{
	if (lista.size()==1) {
		list<int>::iterator iter = lista.begin();
		t_task* task = create_task(*iter);
		create_dependency(fork, task);
		create_dependency(task, join);
	} else if (lista.size()==2) {
		stringstream ss;
		list<int>::iterator iter_1 = lista.begin(), iter_2 = lista.begin();
		iter_2++;
		t_task* task_1 = create_task(*iter_1);
		t_task* task_2 = create_task(*iter_2);
		create_dependency(fork, task_1);
		if (getRnder()->randDouble()>getProbability()) { //sequential
			create_dependency(task_1, task_2);
		} else { //parallel
			create_dependency(fork, task_2);
			create_dependency(task_1, join);
		}
		create_dependency(task_2, join);
	} else { //(lista.size()>2
		int split_point = getRnder()->randInt(lista.size()-2)+2;
		list<int> list_1, list_2;
		list<int>::iterator it_from = lista.begin(), it_to = lista.begin();
		advance(it_to, split_point);
		list_1.insert(list_1.begin(), it_from, it_to);

		it_from = it_to;
		it_to = lista.end();
		list_2.insert(list_2.begin(), it_from, it_to);

		if (getRnder()->randDouble()>getProbability()) { //sequential
			t_task* sync  =  create_sync();
			generate_tasks_internal(fork, sync, list_1);
			generate_tasks_internal(sync, join, list_2);
		} else { //parallel
			generate_tasks_internal(fork, join, list_1);
			generate_tasks_internal(fork, join, list_2);
		}
	}
}

void CodeStyleSoftwareGenerator::generate_tasks ()
{
	root = create_sync();
	t_task* join = create_sync();

	list<int> lista;

	for (int i=0; i<SoftwareGenerator::getTaskNumber(); i++)
		lista.push_back(i);

	generate_tasks_internal(root, join, lista);
}


/********************************* GENERATION *********************************/

void CodeStyleSoftwareGenerator::_generate ()
{
	generate_tasks();
	simplify();
}

void CodeStyleSoftwareGenerator::simplify ()
{
	//look for useless sync task, for example (a, b: tasks, s: sync task):
	//a->s->b
	std::list<t_task*>::iterator it = tasks.begin();
	while (it!=tasks.end()) {
		t_sync_task* tmp = dynamic_cast<t_sync_task*>(*it);
		std::list<t_task*>::iterator it_copy = it;
		it++;
		if (tmp!=NULL && 
				( (tmp->getDepsIn()==1 && tmp->getDepsOut()!=0) ||
				  (tmp->getDepsOut()==1 && tmp->getDepsIn()!=0) ) ) {
		for (t_task::DependencyIterator depOut=tmp->beginOut();
												depOut!=tmp->endOut(); depOut++)
			for (t_task::DependencyIterator depIn=tmp->beginIn();
												 depIn!=tmp->endIn(); depIn++) {
					t_task* from = (*depIn)->getPre();
					t_task* to = (*depOut)->getPost();
					from->eraseDepOut(tmp);
					to->eraseDepIn(tmp);
					depNumber--;
					create_dependency (from, to);
				}
			depNumber--;
			tasks.erase(it_copy);
		}
	}
}

