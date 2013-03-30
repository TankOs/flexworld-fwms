#include <FWMS/ReaderLink.hpp>
#include <FWMS/Router.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestReaderLink ) {
	using namespace ms;

	// Link and unlink.
	{
		Router router;

		{
			ReaderLink link_0( router, []( const Message& ) {} );
			BOOST_CHECK( router.get_num_readers() == 1 );

			{
				ReaderLink link_1( router, []( const Message& ) {} );
				BOOST_CHECK( router.get_num_readers() == 2 );

				{
					ReaderLink link_2( router, []( const Message& ) {} );
					BOOST_CHECK( router.get_num_readers() == 3 );
				}

				BOOST_CHECK( router.get_num_readers() == 2 );
			}

			BOOST_CHECK( router.get_num_readers() == 1 );
		}

		BOOST_CHECK( router.get_num_readers() == 0 );
	}
}
