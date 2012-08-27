#include <FWMS/Reader.hpp>

namespace ms {

Reader::Reader() {
}

Reader::~Reader() {
}

void Reader::pass_message( const Message& message ) {
	handle_message( message );
}

}
