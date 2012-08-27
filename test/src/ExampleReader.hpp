#pragma once

#include <FWMS/Reader.hpp>
#include <FWMS/Hash.hpp>

class ExampleReader : public ms::Reader {
	public:
		static const ms::HashValue MSGA_ID;
		static const ms::HashValue MSGB_ID;
		static const ms::HashValue MSGC_ID;
		static const ms::HashValue FLOAT_PROP_ID;
		static const ms::HashValue INT_PROP_ID;

		ExampleReader();

		void handle_message( const ms::Message& message );

		std::size_t num_handled_messages;
		std::size_t num_unhandled_messages;
		std::size_t num_a_messages;
		std::size_t num_c_messages;
		bool property_checks_enabled;
};

