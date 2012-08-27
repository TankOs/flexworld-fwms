#include "ExampleReader.hpp"

#include <FWMS/Message.hpp>

#include <boost/test/unit_test.hpp>

const ms::HashValue ExampleReader::MSGA_ID = ms::string_hash( "message_a" );
const ms::HashValue ExampleReader::MSGB_ID = ms::string_hash( "message_b" );
const ms::HashValue ExampleReader::MSGC_ID = ms::string_hash( "message_c" );
const ms::HashValue ExampleReader::FLOAT_PROP_ID = ms::string_hash( "float" );
const ms::HashValue ExampleReader::INT_PROP_ID = ms::string_hash( "int" );

ExampleReader::ExampleReader() :
	ms::Reader(),
	num_handled_messages( 0 ),
	num_unhandled_messages( 0 ),
	num_a_messages( 0 ),
	num_c_messages( 0 )
{
}

void ExampleReader::handle_message( const ms::Message& message ) {
	ms::HashValue id = message.get_id();

	if( id == MSGA_ID ) {
		const float* property = message.find_property<float>( FLOAT_PROP_ID );
		BOOST_CHECK( property != nullptr );

		if( property != nullptr ) {
			BOOST_CHECK( *property == 123.4f );
		}

		++num_a_messages;
		++num_handled_messages;
	}
	else if( id == MSGC_ID ) {
		const int* property = message.find_property<int>( INT_PROP_ID );
		BOOST_CHECK( property != nullptr );

		if( property != nullptr ) {
			BOOST_CHECK( *property == 1234 );
		}

		++num_c_messages;
		++num_handled_messages;
	}
	else {
		++num_unhandled_messages;
	}
}
