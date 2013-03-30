#pragma once

#include <vector>
#include <memory>
#include <deque>
#include <mutex>

namespace ms {

class Reader;
class Message;

/** Router.
 * The router delivers messages to all registered reader functions.
 */
class Router {
	public:
		typedef
			std::function<void( const Message& )>
			ReaderFunction
		; ///< Reader function type.

		/** Ctor.
		 */
		Router();

		/** Dtor.
		 */
		~Router();

		/** Get number of registered readers.
		 * @return Number of readers.
		 */
		std::size_t get_num_readers() const;

		/** Add reader.
		 * @param reader Reader.
		 * @return Unique reader ID.
		 */
		uint32_t add_reader( ReaderFunction reader );

		/** Remove previously added reader.
		 * @param id Reader ID (must be valid).
		 */
		void remove_reader( uint32_t id );

		/** Enqueue a message.
		 * The message will be held in a queue until process_queue() is called.
		 * This method is fully thread-safe, just make sure to call process_queue()
		 * from a specific (main?) thread.
		 * @param message Message.
		 */
		void enqueue_message( std::shared_ptr<const Message> message );

		/** Get size of message queue.
		 * @return Size of message queue.
		 */
		std::size_t get_queue_size() const;

		/** Process message queue.
		 */
		void process_queue();

	private:
		typedef std::pair<uint32_t, ReaderFunction> IDReaderPair;
		typedef std::vector<IDReaderPair> ReaderArray;
		typedef std::deque<std::shared_ptr<const Message>> MessageDeque;

		ReaderArray m_readers;
		MessageDeque m_messages;

		uint32_t m_next_reader_id;

		mutable std::mutex m_mutex;
};

}
