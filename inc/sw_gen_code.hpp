#ifndef __SOFTWARE_GENERATOR_CODESTYLE_HPP__
#define __SOFTWARE_GENERATOR_CODESTYLE_HPP__


#include <vector>
#include <list>

#include <sw_gen.hpp>


/*! \brief provide something that looks like software concurrency
 *
 * The generation process divides the task set in two sets and randomly decides
 * if these two groups are executed either sequentially or in parallel.
 * Then the routine is invoked recursively on each sub group until all the
 * groups contain one or zero tasks.
 * Dependencies are a direct result of the previous step.
 *
 * author Mario Bambagini
 */
class CodeStyleSoftwareGenerator: public SoftwareGenerator
{

	double serPar;	/*<! its value is within [0,1] and defines what is more
									likely:, sequential or parallel execution */

	t_task* root; /*<! Task graph root  */

	int depNumber; /*<! Number of actual dependencies */

	std::list<t_task*> tasks; /*<! Created tasks */

	/*! \brief create a task
	 *
	 *  \param id the id of the new task
	 *  \return the new task
	 */
	t_task* create_task (int id);

	/*! \brief create a synchronization point
	 *
	 *  \return the new element (which is a kind of task)
	 */
	t_task* create_sync ();

	/*! \brief create a bind between two tasks
	 *
	 *  the communication costs are generated
	 *  \param from the dependency goes from this task
	 *  \param to the dependency goes to this task
	 */
	void create_dependency (t_task* from, t_task* to);


	/*! \brief generate the task set */
	void generate_tasks ();

	/*! \brief internal function to generate a sub set of tasks */
	void generate_tasks_internal (t_task* fork, t_task* join,
														  std::list<int> lista);

	/*! \brief simplify the task graph
	 * this function applies several semplifications which were not easy during
	 * the generation process
	 */
	void simplify ();

	/*! \brief generate the problem
	*/
	void _generate ();


protected:

	/*! \brief Specific iterator for CodeStyleSoftwareGenerator
	 *
	 *  This is a basic Iterator, which iterates for each element in
	 *  CodeStyleSoftwareGenerator.tasks
	 */
	class CodeEmulatorIterator : public TaskIterator
	{
		std::list<t_task*>::iterator current;
	public:
		CodeEmulatorIterator(std::list<t_task*>::iterator from) {
			current = from;
		}
		t_task* operator* () const {
			return *current;
		}
		CodeEmulatorIterator* operator++ () {
			current++;
			return this;
		}
		CodeEmulatorIterator* operator++ (int n) {
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

	/*! \brief execute the generation process
	 */
	void generate () {
		depNumber = 0;
		_generate();
	}


	/****************************** PROBABILITIES *****************************/

	/*! \brief return the parallel/sequential probability specified by the user
	 */
	double getProbability () const {
		return serPar;
	}

	/*! \brief set the parallel/sequential probability specified by the user
	 */
	void setProbability (double p) {
		serPar = p;
	}


	/******************************** ITERATOR ********************************/

	/*! \brief return an iterator to the first element in the task graph
	 */
	Iterator begin() {
		return Iterator(new CodeEmulatorIterator(tasks.begin()));
	}

	/*! \brief return an iterator to the last element in the task graph
	 */
	Iterator end() {
		return Iterator(new CodeEmulatorIterator(tasks.end()));
	}


	/******************************** SOFTWARE ********************************/

	/*! \brief return the actual number of generated tasks
	 */
	int getTaskNumber () const {
		return tasks.size();
	}

	/*! \brief return the actual number of dependencies among tasks
	 */
	int getDependencyNumber () const {
		return depNumber;
	}

};

#endif //__SOFTWARE_GENERATOR_CODESTYLE_HPP__

