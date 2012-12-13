#ifndef __SERIALIZER_PLAINTEXT_HPP__
#define __SERIALIZER_PLAINTEXT_HPP__


#include <sw_ser.hpp>


/*! \brief serialize a generated task graph using a plain text format
 *
 * author Mario Bambagini
 */
class SerializerPlainText: public Serializer {

public:

	bool serialize (std::string filename, SoftwareGenerator* gen);

};

#endif //__SERIALIZER_PLAINTEXT_HPP

