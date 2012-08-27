#include "ExampleReader.hpp"

#include <FWMS/Reader.hpp>
#include <FWMS/Message.hpp>
#include <FWMS/Hash.hpp>
#include <FWMS/Router.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestReader ) {
	using namespace ms;

	// Initial state.
	{
		ExampleReader reader;

		BOOST_CHECK( reader.num_handled_messages == 0 );
		BOOST_CHECK( reader.num_unhandled_messages == 0 );
		BOOST_CHECK( reader.num_a_messages == 0 );
		BOOST_CHECK( reader.num_c_messages == 0 );
	}

	// Basic properties.
	{
		Router router;
		ExampleReader reader;

		reader.set_router( &router );
		BOOST_CHECK( reader.get_router() == &router );

		reader.set_router( nullptr );
		BOOST_CHECK( reader.get_router() == nullptr );
	}

	// Send messages.
	{
		Message message_a( ExampleReader::MSGA_ID );
		message_a.set_property<float>( ExampleReader::FLOAT_PROP_ID, 123.4f );

		Message message_b( ExampleReader::MSGB_ID );

		Message message_c( ExampleReader::MSGC_ID );
		message_c.set_property<int>( ExampleReader::INT_PROP_ID, 1234 );

		ExampleReader reader;
		reader.pass_message( message_a );
		reader.pass_message( message_a );
		reader.pass_message( message_a );
		reader.pass_message( message_a );
		reader.pass_message( message_a );
		reader.pass_message( message_a );
		reader.pass_message( message_a );
		reader.pass_message( message_a );
		reader.pass_message( message_b );
		reader.pass_message( message_b );
		reader.pass_message( message_b );
		reader.pass_message( message_c );
		reader.pass_message( message_c );
		reader.pass_message( message_c );

		BOOST_CHECK( reader.num_handled_messages == 11 );
		BOOST_CHECK( reader.num_unhandled_messages == 3 );
		BOOST_CHECK( reader.num_a_messages == 8 );
		BOOST_CHECK( reader.num_c_messages == 3 );
	}
}
