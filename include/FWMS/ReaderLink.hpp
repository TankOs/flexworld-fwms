#pragma once

#include <FWMS/Router.hpp>

namespace ms {

/** Scoped reader link.
 * The reader is automatically removed from the router if this object dies.
 */
class ReaderLink {
	public:
		/** Ctor.
		 * @param router Router.
		 * @param reader Reader function.
		 */
		ReaderLink( Router& router, Router::ReaderFunction reader );

		ReaderLink( const ReaderLink& ) = delete;
		ReaderLink& operator=( const ReaderLink& ) = delete;

		/** Dtor.
		 */
		~ReaderLink();

	private:
		Router& m_router;
		uint32_t m_reader_id;
};

}
