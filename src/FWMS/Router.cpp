#include <FWMS/Router.hpp>
#include <FWMS/Reader.hpp>

namespace ms {

Router::Router() {
}

Router::~Router() {
	for( std::size_t reader_idx = 0; reader_idx < m_readers.size(); ++reader_idx ) {
		delete m_readers[reader_idx];
	}

	m_readers.clear();
}

std::size_t Router::get_num_readers() const {
	return m_readers.size();
}

}
