#include <FWMS/Property.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestProperty ) {
	using namespace ms;

	// Initial state.
	{
		ConcreteProperty<float> float_property( 100.0f );

		BOOST_CHECK( float_property.get_value() == 100.0f );
		BOOST_CHECK( float_property.get_type_id() == typeid( float ).name() );
	}

	// Set value.
	{
		ConcreteProperty<float> float_property( 12345.f );
		float_property.set_value( 321.0f );

		BOOST_CHECK( float_property.get_value() == 321.f );
	}
}
