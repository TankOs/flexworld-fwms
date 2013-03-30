#include <FWMS/ReaderLink.hpp>

namespace ms {

ReaderLink::ReaderLink( Router& router, Router::ReaderFunction reader ) :
	m_router( router ),
	m_reader_id( 0 )
{
	m_reader_id = m_router.add_reader( reader );
}

ReaderLink::~ReaderLink() {
	m_router.remove_reader( m_reader_id );
}

}
