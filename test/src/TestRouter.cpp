#include <FWMS/Router.hpp>
#include <FWMS/Message.hpp>
#include <FWMS/Hash.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestRouter ) {
	using namespace ms;

	// Initial state.
	{
		Router router;

		BOOST_CHECK( router.get_num_readers() == 0 );
	}

	// Add readers.
	{
		Router router;

		uint32_t reader_0_id = router.add_reader( []( const Message& ) {} );
		uint32_t reader_1_id = router.add_reader( []( const Message& ) {} );

		BOOST_CHECK( router.get_num_readers() == 2 );
		BOOST_CHECK( reader_0_id == 0 );
		BOOST_CHECK( reader_1_id == 1 );
	}

	// Remove readers.
	{
		Router router;

		uint32_t id_0 = router.add_reader( []( const Message& ) {} );
		uint32_t id_1 = router.add_reader( []( const Message& ) {} );
		uint32_t id_2 = router.add_reader( []( const Message& ) {} );
		BOOST_CHECK( router.get_num_readers() == 3 );

		router.remove_reader( id_2 );
		router.remove_reader( id_0 );
		router.remove_reader( id_1 );
		BOOST_CHECK( router.get_num_readers() == 0 );
	}

	// Enqueue messages.
	{
		Router router;

		router.enqueue_message(
			std::make_shared<Message>( string_hash( "a" ) )
		);
		router.enqueue_message(
			std::make_shared<Message>( string_hash( "b" ) )
		);
		router.enqueue_message(
			std::make_shared<Message>( string_hash( "c" ) )
		);

		BOOST_CHECK( router.get_queue_size() == 3 );
	}

	// Process router message queue.
	{
		Router router;
		uint32_t num_a_messages = 0;
		uint32_t num_b_messages = 0;
		uint32_t num_c_messages = 0;

		router.add_reader(
			[&num_a_messages, &num_b_messages, &num_c_messages]
			( const Message& msg ) {
				if( msg.get_id() == string_hash( "a" ) ) {
					++num_a_messages;
				}
				else if( msg.get_id() == string_hash( "b" ) ) {
					++num_b_messages;
				}
				else if( msg.get_id() == string_hash( "c" ) ) {
					++num_c_messages;
				}
			}
		);

		router.enqueue_message( std::make_shared<Message>( string_hash( "a" ) ) );
		router.enqueue_message( std::make_shared<Message>( string_hash( "b" ) ) );
		router.enqueue_message( std::make_shared<Message>( string_hash( "b" ) ) );
		router.enqueue_message( std::make_shared<Message>( string_hash( "c" ) ) );
		router.enqueue_message( std::make_shared<Message>( string_hash( "c" ) ) );
		router.enqueue_message( std::make_shared<Message>( string_hash( "c" ) ) );

		router.process_queue();
		BOOST_CHECK( router.get_queue_size() == 0 );

		BOOST_CHECK( num_a_messages == 1 );
		BOOST_CHECK( num_b_messages == 2 );
		BOOST_CHECK( num_c_messages == 3 );
	}
}
