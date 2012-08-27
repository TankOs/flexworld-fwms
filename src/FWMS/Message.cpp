#include <FWMS/Message.hpp>

namespace ms {

Message::Message( HashValue id ) :
	m_id( id )
{
}

Message::~Message() {
	PropertyMap::iterator prop_iter = m_properties.begin();
	PropertyMap::iterator prop_iter_end = m_properties.end();
	
	for( ; prop_iter != prop_iter_end; ++prop_iter ) {
		delete prop_iter->second;
	}

	m_properties.clear();
}

HashValue Message::get_id() const {
	return m_id;
}

std::size_t Message::get_num_properties() const {
	return m_properties.size();
}

}
