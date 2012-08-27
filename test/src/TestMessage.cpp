#include <FWMS/Message.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestMessage ) {
	using namespace ms;

	static const HashValue ID = string_hash( "foobar" );

	// Initial state.
	{
		Message message( ID );

		BOOST_CHECK( message.get_id() == ID );
		BOOST_CHECK( message.get_num_properties() == 0 );
	}

	// Properties.
	{
		static const HashValue FLOAT_PROP_ID = string_hash( "float" );
		static const HashValue INT_PROP_ID = string_hash( "int" );
		static const HashValue STRING_PROP_ID = string_hash( "string" );

		Message message( ID );

		message.set_property<float>( FLOAT_PROP_ID, 40.0f );
		message.set_property<int>( INT_PROP_ID, 80 );
		message.set_property<std::string>( STRING_PROP_ID, "160" );

		BOOST_CHECK( message.get_num_properties() == 3 );
		BOOST_REQUIRE( message.find_property<float>( FLOAT_PROP_ID ) != nullptr );
		BOOST_REQUIRE( message.find_property<int>( INT_PROP_ID ) != nullptr );
		BOOST_REQUIRE( message.find_property<std::string>( STRING_PROP_ID ) != nullptr );
		BOOST_CHECK( *message.find_property<float>( FLOAT_PROP_ID ) == 40.0f );
		BOOST_CHECK( *message.find_property<int>( INT_PROP_ID ) == 80 );
		BOOST_CHECK( *message.find_property<std::string>( STRING_PROP_ID ) == "160" );
	}
}
