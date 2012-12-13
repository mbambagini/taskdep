#ifndef __RANDOMIZER_H__
#define __RANDOMIZER_H__


#include <cstdlib>


/*! \brief Uniform random number generator
 *
 * author Mario Bambagini
 */
class Randomizer {

public:

	Randomizer();

	/*! \brief generate a double whitin [0,1]
	 */
	virtual double randDouble () {
		return (double)rand()/RAND_MAX;
	}

	/*! \brief generate an integer whitin [0,max-1]
	 */
	virtual int randInt(int max) {
		return rand()%max;
	}

};


#endif //__RANDOMIZER_H__

