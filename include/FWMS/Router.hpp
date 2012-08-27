#pragma once

#include <vector>

namespace ms {

class Reader;

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

	private:
		typedef std::vector<Reader*> ReaderArray;

		ReaderArray m_readers;
};

}

#include "Router.inl"
