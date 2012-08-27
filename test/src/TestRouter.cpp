#include "ExampleReader.hpp"

#include <FWMS/Router.hpp>

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
	}
}
