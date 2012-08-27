#pragma once

#include <vector>
#include <memory>
#include <deque>

#include <boost/thread/mutex.hpp>

namespace ms {

class Reader;
class Message;

/** Router.
 * The router creates readers and passes message to all registered ones.
 */
class Router {
	public:
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

		/** Create reader.
		 * @tparam T Reader type.
		 * @return Created reader (also stored internally in router).
		 */
		template <class T>
		T& create_reader();

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
		typedef std::vector<Reader*> ReaderArray;
		typedef std::deque<std::shared_ptr<const Message>> MessageDeque;

		ReaderArray m_readers;
		MessageDeque m_messages;

		mutable boost::mutex m_mutex;
};

}

#include "Router.inl"
