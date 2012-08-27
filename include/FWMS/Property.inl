#include <typeinfo>

namespace ms {

template <class T>
ConcreteProperty<T>::ConcreteProperty( const T& initial_value ) :
	m_data( initial_value )
{
}

template <class T>
void ConcreteProperty<T>::set_value( const T& value ) {
	m_data = value;
}

template <class T>
const T& ConcreteProperty<T>::get_value() const {
	return m_data;
}

template <class T>
const std::string& ConcreteProperty<T>::get_type_id() const {
	static std::string type_id = typeid( T ).name();

	return type_id;
}

}
