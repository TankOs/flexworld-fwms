#include <FWMS/Reader.hpp>
#include <FWMS/Message.hpp>
#include <FWMS/Hash.hpp>

#include <boost/test/unit_test.hpp>

static const ms::HashValue MSGA_ID = ms::string_hash( "message_a" );
static const ms::HashValue MSGB_ID = ms::string_hash( "message_b" );
static const ms::HashValue MSGC_ID = ms::string_hash( "message_c" );
static const ms::HashValue FLOAT_PROP_ID = ms::string_hash( "float" );
static const ms::HashValue INT_PROP_ID = ms::string_hash( "int" );

class ExampleReader : public ms::Reader {
	public:
		ExampleReader() :
			ms::Reader(),
			num_handled_messages( 0 ),
			num_unhandled_messages( 0 ),
			num_a_messages( 0 ),
			num_c_messages( 0 )
		{
		}

		void handle_message( const ms::Message& message ) {
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

		std::size_t num_handled_messages;
		std::size_t num_unhandled_messages;
		std::size_t num_a_messages;
		std::size_t num_c_messages;
};

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

	// Send messages.
	{
		Message message_a( MSGA_ID );
		message_a.set_property<float>( FLOAT_PROP_ID, 123.4f );

		Message message_b( MSGB_ID );

		Message message_c( MSGC_ID );
		message_c.set_property<int>( INT_PROP_ID, 1234 );

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
