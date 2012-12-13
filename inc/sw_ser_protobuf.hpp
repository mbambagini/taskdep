#ifndef __SERIALIZER_PROTOBUF_HPP__
#define __SERIALIZER_PROTOBUF_HPP__


#include <sw_ser.hpp>


/*! \brief serialize a generated task graph using protobuf
 *
 * author Mario Bambagini
 */
class SerializerProtobuf: public Serializer {

public:

	bool serialize (std::string filename, SoftwareGenerator* gen);

};

#endif //__SERIALIZER_PROTOBUF_HPP

