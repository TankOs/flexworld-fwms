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

void Router::enqueue_message( std::shared_ptr<const Message> message ) {
	boost::lock_guard<boost::mutex> lock( m_mutex );

	m_messages.push_back( message );
}

std::size_t Router::get_queue_size() const {
	std::size_t size = 0;

	{
		boost::lock_guard<boost::mutex> lock( m_mutex );

		size = m_messages.size();
	}

	return size;
}

void Router::process_queue() {
	std::shared_ptr<const Message> message;
	std::size_t num_readers = m_readers.size();

	while( true ) {
		{
			boost::lock_guard<boost::mutex> lock( m_mutex );

			if( m_messages.size() == 0 ) {
				break;
			}

			message = m_messages.front();
			m_messages.pop_front();
		}

		for( std::size_t reader_idx = 0; reader_idx < num_readers; ++reader_idx ) {
			m_readers[reader_idx]->pass_message( *message );
		}
	}
}

}
