#ifndef __DATA_FLOW_GENERATOR_HPP__
#define __DATA_FLOW_GENERATOR_HPP__

#include <vector>
#include <list>

#include <sw_gen.hpp>


/*! \brief classical task generator
 *
 * First of all, the algorithm creates the tasks.
 * Then, it creates the specified number of dependencies by picking randomly
 * the task pairs among the entire task set (with a maximum task distance).
 *
 * autohr Mario Bambagini
 */
class DataFlowSoftwareGenerator: public SoftwareGenerator
{

	int nOfDependencies; /*<! Number of actual dependencies */

	int maxDependencyDistance; /*<! Max distance between two tasks linked by a
																   dependency */

	std::vector<t_task*> tasks; /*<! Created tasks */

	std::list<t_dependency*> dependencies; /*<! Created dependencies */

	/*! \brief generate the task set */
	void generate_tasks ();

	/*! \brief generate the dependency set */
	void generate_dependencies();

protected:

	/*! \brief specific iterator for this class
	 */
	class DataFlowIterator : public TaskIterator
	{
		std::vector<t_task*>::iterator current;
	public:

		DataFlowIterator(std::vector<t_task*>::iterator from) {
			current = from;
		}

		t_task* operator* () const {
			return *current;
		}

		DataFlowIterator* operator++ () {
			current++;
			return this;
		}

		DataFlowIterator* operator++ (int n) {
			current++;
			return this;
		}

		bool operator== (TaskIterator* arg) {
			if ((*current)==(**arg))
				return true;
			return false;
		}

		bool operator!= (TaskIterator* arg) {
			if ((*current)==(**arg))
				return false;
			return true;
		}
	};


public:

	void generate () {
		generate_tasks();
		generate_dependencies();
	}


	/******************************** ITERATOR ********************************/

	/*! \brief return an iterator to the first element in the task graph
	 */
	Iterator begin() {
		return Iterator(new DataFlowIterator(tasks.begin()));
	}

	/*! \brief return an iterator to the last element in the task graph
	 */
	Iterator end() {
		return Iterator(new DataFlowIterator(tasks.end()));
	}


	/******************************** SOFTWARE ********************************/

	/*! \brief return the desired number of dependencies
	 */
	int getDependencyNumber () const {
		return nOfDependencies;
	}

	/*! \brief set the desired number of dependencies
	 */
	void setDependencyNumber (int n) {
		nOfDependencies = n;
	}

	/*! \brief return the maximum distance between two tasks linked by a
	 *  precedence constraint
	 */
	int getMaxDependencyDistance () const {
		return maxDependencyDistance;
	}

	/*! \brief set the maximum distance between two tasks linked by a dependency
	 */
	void setMaxDependencyDistance (int d) {
		maxDependencyDistance = d;
	}

};

#endif //__DATA_FLOW_GENERATOR_HPP__

