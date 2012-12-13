#ifndef __GENERATOR_H__
#define __GENERATOR_H__


#include <randomizer.hpp>
#include <task.hpp>


/*! \brief Abstract generation class for the software
 * 
 * author Mario Bambagini
 */
class SoftwareGenerator
{

	Randomizer* rnd; /*<! it allows you to customize the randomizer in use */

	int maxWcet; /*<! max possible WCET */
	int minWcet; /*<! min possible WCET */

	int maxExchangedData; /*<! max amount of exchanged data */
	int minExchangedData; /*<! min amount of exchanged data */

	int nOfTasks; /*<! Number of tasks to generate */

protected:

	/*! \brief internal iterator
	 */
	class TaskIterator
	{
	public:

		virtual t_task* operator* () const = 0;

		virtual TaskIterator* operator++ () = 0;

		virtual TaskIterator* operator++ (int n) = 0;

		virtual bool operator== (TaskIterator* arg) = 0;
		virtual bool operator!= (TaskIterator* arg) = 0;
	};

public:

	/*! \brief generate the problem (task set and execution environment)
	 */
	virtual void generate () = 0;


	/******************************** ITERATOR ********************************/

	/*! \brief iterator wrapper
	 * it is necessary to wrap the custom iterators which are defined by the
	 * derived classes
	 */
	class Iterator
	{
		TaskIterator* iter;
	public:

		Iterator (TaskIterator* it) {
			iter = it;
		}

		t_task* operator* () {
			return *(*iter);
		}

		Iterator& operator++ () {
			(*iter)++;
			return *this;
		}

		Iterator& operator++ (int n) {
			(*iter)++;
			return *this;
		}

		bool operator== (Iterator const & arg) {
			if ( (*(*(arg.iter))) == *(*iter) )
				return true;
			return false;
		}

		bool operator!= (Iterator const & arg) {
			if ( (*(*(arg.iter))) != *(*iter) )
				return true;
			return false;
		}
	};

	/*! \brief return an iterator which points to the first element
	 */
	virtual Iterator begin() = 0;

	/*! \brief return an iterator which points to the last element
	 */
	virtual Iterator end() = 0;


	/******************************* RANDOMIZER *******************************/

	/*! \brief return the randomizer in use
	 */
	Randomizer* getRnder () const {
		return rnd;
	}

	/*! \brief set a randomizer to use
	 */
	void setRnder (Randomizer* rnd) {
		this->rnd = rnd;
	}


	/******************************* PARAMETERS *******************************/

	/*! \brief return the task number specified from the user
	 */
	virtual int getTaskNumber () const {
		return nOfTasks;
	}

	/*! \brief set the task number
	*/
	void setTaskNumber (int n) {
		nOfTasks = n;
	}

	/*! \brief return the maximum WCET
	*/
	int getMaxWcet () const {
		return maxWcet;
	}
	/*! \brief set the maximum WCET
	*/
	void setMaxWcet (int val) {
		maxWcet = val;
	}

	/*! \brief return the minimum WCET
	*/
	int getMinWcet () const {
		return minWcet;
	}

	/*! \brief set the minimum WCET
	*/
	void setMinWcet (int val) {
		minWcet = val;
	}

	/*! \brief return the maximum amount of exchanged data between two tasks
	 */
	int getMaxExchangedData () const {
		return maxExchangedData;
	}

	/*! \brief set the maximum amount of exchanged data between two tasks
	 */
	void setMaxExchangedData (int n) {
		maxExchangedData = n;
	}

	/*! \brief return the minimum amount of exchanged data between two tasks
	 */
	int getMinExchangedData () const {
		return minExchangedData;
	}

	/*! \brief set the minimum amount of exchanged data between two tasks
	 */
	void setMinExchangedData (int n) {
		minExchangedData = n;
	}

	/*! \brief return the actual dependency number
	 */
	virtual int getDependencyNumber () const = 0;

};

#endif //__GENERATOR_H__

