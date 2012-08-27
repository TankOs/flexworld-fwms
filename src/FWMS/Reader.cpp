#include <FWMS/Reader.hpp>

namespace ms {

Reader::Reader() :
	m_router( nullptr )
{
}

Reader::~Reader() {
}

void Reader::pass_message( const Message& message ) {
	handle_message( message );
}

void Reader::set_router( Router* router ) {
	m_router = router;
}

Router* Reader::get_router() const {
	return m_router;
}

}
