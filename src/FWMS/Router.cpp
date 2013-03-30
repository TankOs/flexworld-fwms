#include <FWMS/Router.hpp>
#include <FWMS/Reader.hpp>

#include <algorithm>
#include <cassert>

namespace ms {

Router::Router() :
	m_next_reader_id( 0 )
{
}

Router::~Router() {
}

std::size_t Router::get_num_readers() const {
	return m_readers.size();
}

void Router::enqueue_message( std::shared_ptr<const Message> message ) {
	std::lock_guard<std::mutex> lock( m_mutex );

	m_messages.push_back( message );
}

std::size_t Router::get_queue_size() const {
	std::size_t size = 0;

	{
		std::lock_guard<std::mutex> lock( m_mutex );

		size = m_messages.size();
	}

	return size;
}

void Router::process_queue() {
	std::shared_ptr<const Message> message;
	std::size_t num_readers = m_readers.size();

	while( true ) {
		{
			std::lock_guard<std::mutex> lock( m_mutex );

			if( m_messages.size() == 0 ) {
				break;
			}

			message = m_messages.front();
			m_messages.pop_front();
		}

		for( std::size_t reader_idx = 0; reader_idx < num_readers; ++reader_idx ) {
			m_readers[reader_idx].second( *message );
		}
	}
}

uint32_t Router::add_reader( ReaderFunction reader ) {
	std::lock_guard<std::mutex> lock_guard( m_mutex );

	IDReaderPair pair( m_next_reader_id, reader );
	m_readers.push_back( pair );

	return m_next_reader_id++;
}

template <class T>
bool compare_id_reader_pairs(
	const T& first,
	const uint32_t& second
) {
	return first.first < second;
}

void Router::remove_reader( uint32_t id ) {
	auto reader_iter = std::lower_bound(
		std::begin( m_readers ),
		std::end( m_readers ),
		id,
		&compare_id_reader_pairs<IDReaderPair>
	);

	assert( reader_iter != std::end( m_readers ) );
	assert( reader_iter->first == id );

	m_readers.erase( reader_iter );
}

}
