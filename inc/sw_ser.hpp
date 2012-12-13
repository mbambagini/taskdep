#ifndef __SERIALIZER_HPP__
#define __SERIALIZER_HPP__


#include <string.h>
#include <sw_gen.hpp>


/*! \brief Generic serializer
 * 
 * This class takes a generated problem and saves it into the specified file
 *
 * Pattern: Strategy
 *
 * author Mario Bambagini
 */
class Serializer {

public:

	/*! \brief Serialize the file
	 *
	 * \param filename destination file
	 * \param gen generated problem to save
	 * \return true if it executed successfully, false otherwise
	 */
	virtual bool serialize (std::string filename, SoftwareGenerator* gen) = 0;

	virtual ~Serializer() {}
};

#endif //__SERIALIZER_HPP__

