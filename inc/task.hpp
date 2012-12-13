#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <string>
#include <list>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>


class t_task;


/*! \brief Precedence constraint
 *
 * Contain a pointer to the previous and next tasks and the relative amount of
 * exchanged data
 */
class t_dependency
{
	t_task* pre; /*<! previous task */
	t_task* post; /*<! next task */
	int cost_post; /*<! amount of exchanged data */

public:

	/*! \brief return next task
     */
	t_task* getPost () const {
		return post;
	}

	/*! \brief set next task
     */
	void setPost (t_task* task) {
		post = task;
	}

	/*! \brief return the previous task
     */
	t_task* getPre () const {
		return pre;
	}

	/*! \brief set the previous task
     */
	void setPre (t_task* task) {
		pre = task;
	}

	/*! \brief return the amount of exchanged data
     */
	int getCost () const {
		return cost_post;
	}

	/*! \brief set the amount of exchanged data
     */
	void setCost (int cost) {
		cost_post = cost;
	}
};


/*! \brief Represent a generic computational task
 */
class t_task
{
private:
	std::list<t_dependency*> depIn; /*<! All dependencies that point to him */
	std::list<t_dependency*> depOut; /*<! All dependencies that strart from
																		  him */

	int id; /*<! Task ID */
	std::string name; /*<! Task name */

protected:

	/*! \brief set task ID
	 */
	void _setId(int id) {
		this->id = id;
	}

	/*! \brief set task name
	 */
	void _setName(std::string name) {
		this->name = name;
	}

public:

	/**************************************************************************
	 * ITERATORS
	 **************************************************************************/

	/*! \brief Iterator to explore all the related dependencies
	 */
	class DependencyIterator
	{
		std::list<t_dependency*>::iterator current;
	public:
		DependencyIterator(std::list<t_dependency*>::iterator elem) {
			current = elem;
		}
		t_dependency* operator* () const {
			return *current;
		}
		DependencyIterator& operator++ () {
			current++;
			return *this;
		}
		DependencyIterator& operator++ (int n) {
			current++;
			return *this;
		}
		bool operator== (DependencyIterator const & arg) {
			if ((*current)==(*(arg.current)))
				return true;
			return false;
		}
		bool operator!= (DependencyIterator const & arg) {
			if ((*current)==(*(arg.current)))
				return false;
			return true;
		}
	};


	/*! \brief return an iterator which points to the first out dependency
	 *
	 * Although this function is redundant, it has been inserted for
	 * compatibility
	 */
	DependencyIterator begin() {
		return beginOut();
	}

	/*! \brief return an iterator which points to the last out dependency
	 *
	 * Although this function is redundant, it has been inserted for
	 * compatibility
	 */
	DependencyIterator end() {
		return endOut();
	}

	/*! \brief return an iterator which points to the first out dependency
	 */
	DependencyIterator beginOut() {
		return DependencyIterator(depOut.begin());
	}

	/*! \brief return an iterator which points to the last out dependency
	 */
	DependencyIterator endOut() {
		return DependencyIterator(depOut.end());
	}

	/*! \brief return an iterator which points to the first in dependency
	 */
	DependencyIterator beginIn() {
		return DependencyIterator(depIn.begin());
	}

	/*! \brief return an iterator which points to the last in dependency
	 */
	DependencyIterator endIn() {
		return DependencyIterator(depIn.end());
	}


	/**************************************************************************
	 * PARAMETERS
	 **************************************************************************/

	/*! \brief set the task ID
	 */
	virtual void setID (int id) = 0;

	/*! \brief return the task ID
	 */
	int getID () {
		return id;
	}

	/*! \brief return the task name
	 */
	std::string getName () const {
		return name;
	}

	/*! \brief return the worst-case execution time
	 */
	virtual int getWcet () const = 0;

	/*! \brief set the worst-case execution time
	 */
	virtual void setWcet (int value) = 0;


	/**************************************************************************
	 * DEPENDENCIES
	 **************************************************************************/

	/*! \brief make a dependency start from it
	 */
	void addDepOut (t_dependency* dep) {
		depOut.push_back(dep);
	}

	/*! \brief return the number of dependencies that start from it
	 */
	int getDepsOut () {
		return depOut.size();
	}

	/*! \brief remove a dependency that starts from it
	 */
	void eraseDepOut (t_task* task) {
		for (std::list<t_dependency*>::iterator dep = depOut.begin();
													   dep!=depOut.end(); dep++)
			if ((*dep)->getPost()==task) {
				depOut.erase(dep);
				return;
			}
	}

	/*! \brief make a dependency arrive to it
	 */
	void addDepIn (t_dependency* dep) {
		depIn.push_back(dep);
	}

	/*! \brief return the number of dependencies that arrive to it
	 */
	int getDepsIn () {
		return depIn.size();
	}

	/*! \brief remove a dependency that arrives to it
	 */
	void eraseDepIn (t_task* task) {
		for (std::list<t_dependency*>::iterator dep = depIn.begin();
														dep!=depIn.end(); dep++)
			if ((*dep)->getPre()==task) {
				depIn.erase(dep);
				return;
			}
	}
};


/*! \brief classical task
 */
class t_real_task: public t_task
{
	int wcet;

public:
	t_real_task():t_task() {
		wcet = 0;
	}

	void setID (int id) {
		_setId(id);
		std::stringstream ss;
		ss <<"T"<<id;
		_setName(ss.str());
	}

	int getWcet () const {
		return wcet;
	}

	void setWcet (int value) {
		wcet = value;
	}
};


/*! \brief task with no computational time that models a synchronization point
 */
class t_sync_task: public t_task
{
	static int number;

public:
	t_sync_task():t_task() {
		_setId(number++);
		std::stringstream ss;
		ss <<"S"<<number;
		_setName(ss.str());
	}

	void setID (int id) {}

	int getWcet () const {
		return 0;
	};

	void setWcet (int value) {}
};


#endif //__TASK_HPP__

