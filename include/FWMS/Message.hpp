#pragma once

#include <FWMS/Property.hpp>
#include <FWMS/Hash.hpp>

#include <map>
#include <string>
#include <cassert>

namespace ms {

class Property;

/** Message.
 * The message is identified by an ID and carries properties (information).
 *
 * The ID can either be directly set using a numeric value or one can set a
 * string, which is then hashed to a number. For hashing, ms::string_hash is
 * being used.
 */

class Message {
	public:
		/** Ctor.
		 * @param id ID.
		 */
		Message( HashValue id );

		/** Dtor.
		 */
		~Message();

		/** Copy ctor.
		 * @param other Other.
		 */
		Message( const Message& other ) = delete;

		/** Assignment.
		 * @param other Other.
		 */
		Message& operator=( const Message& other ) = delete;

		/** Get ID.
		 * @return ID.
		 */
		HashValue get_id() const;

		/** Get number of properties.
		 * @return Number of properties.
		 */
		std::size_t get_num_properties() const;

		/** Set property.
		 * The property will be created if it doesn't exist yet.
		 * @param id ID.
		 * @param value Value.
		 * @tparam T Type.
		 */
		template <class T>
		void set_property( HashValue id, const T& value );

		/** Find property.
		 * In debug mode the requested type is checked against the stored type. If
		 * the type mismatches, an assertion will fail. Undefined behaviour in
		 * release mode.
		 * @param id ID.
		 * @tparam T Type.
		 * @return Pointer to value or nullptr if not found.
		 */
		template <class T>
		const T* find_property( HashValue id ) const;

	private:
		typedef std::map<HashValue, Property*> PropertyMap;

		PropertyMap m_properties;
		HashValue m_id;
};

}

#include "Message.inl"
