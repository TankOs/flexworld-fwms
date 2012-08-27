#pragma once

#include <string>

namespace ms {

/** Property.
 * Baseclass for concrete properties with a specific type. Used internally.
 */
class Property {
	public:
		/** Dtor.
		 */
		virtual ~Property();

		/** Get type ID.
		 * This value is compiler-dependent!
		 * @return Type ID.
		 */
		virtual const std::string& get_type_id() const = 0;
};

/** Concrete property, i.e. fixed value type.
 * @tparam T Value type.
 */
template <class T>
class ConcreteProperty : public Property {
	public:
		/** Ctor.
		 * @param initial_value Initial value.
		 */
		ConcreteProperty( const T& initial_value = T() );

		/** Set value.
		 * @param value Value.
		 */
		void set_value( const T& value );

		/** Get value.
		 * @return Value.
		 */
		const T& get_value() const;

		const std::string& get_type_id() const;

	private:
		T m_data;
};

}

#include "Property.inl"
