#ifndef __SERIALIZER_GRAPHVIZ_HPP__
#define __SERIALIZER_GRAPHVIZ_HPP__


#include <sw_ser.hpp>


/*! \brief serialize a generated task graph using the DOT language
 *
 * the DOT language is used from the software Graphviz to draw graph
 *
 * author Mario Bambagini
 *
 */
class SerializerGraphviz: public Serializer {

public:

	bool serialize (std::string filename, SoftwareGenerator* gen);

};

#endif //__SERIALIZER_GRAPHVIZ_HPP

