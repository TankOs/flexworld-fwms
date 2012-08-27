#include "ExampleReader.hpp"

#include <FWMS/Router.hpp>
#include <FWMS/Message.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestRouter ) {
	using namespace ms;

	// Initial state.
	{
		Router router;

		BOOST_CHECK( router.get_num_readers() == 0 );
	}

	// Register readers.
	{
		Router router;

		ExampleReader& reader_a = router.create_reader<ExampleReader>();
		ExampleReader& reader_b = router.create_reader<ExampleReader>();

		BOOST_CHECK( router.get_num_readers() == 2 );
		BOOST_CHECK( &reader_a != &reader_b );

		BOOST_CHECK( reader_a.get_router() == &router );
		BOOST_CHECK( reader_b.get_router() == &router );
	}

	// Enqueue messages.
	{
		Router router;

		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGA_ID ) ) );
		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGB_ID ) ) );
		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGC_ID ) ) );

		BOOST_CHECK( router.get_queue_size() == 3 );
	}

	// Process router message queue.
	{
		Router router;
		ExampleReader& reader = router.create_reader<ExampleReader>();
		reader.property_checks_enabled = false;

		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGA_ID ) ) );
		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGA_ID ) ) );
		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGB_ID ) ) );
		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGB_ID ) ) );
		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGC_ID ) ) );
		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGC_ID ) ) );
		router.enqueue_message( std::shared_ptr<Message>( new Message( ExampleReader::MSGC_ID ) ) );

		router.process_queue();
		BOOST_CHECK( router.get_queue_size() == 0 );

		BOOST_CHECK( reader.num_handled_messages == 5 );
		BOOST_CHECK( reader.num_unhandled_messages == 2 );
		BOOST_CHECK( reader.num_a_messages == 2 );
		BOOST_CHECK( reader.num_c_messages == 3 );
	}
}
