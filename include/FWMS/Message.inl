namespace ms {

template <class T>
void Message::set_property( HashValue id, const T& value ) {
	PropertyMap::iterator prop_iter = m_properties.find( id );

	if( prop_iter == m_properties.end() ) {
		// Create new.
		m_properties[id] = new ConcreteProperty<T>( value );
	}
	else {
#ifndef NDEBUG
		ConcreteProperty<T>* c_prop = dynamic_cast<ConcreteProperty<T>*>( prop_iter->second );
		assert( c_prop != nullptr && "Property found but type mismatched." );
#else
		ConcreteProperty<T>* c_prop = reinterpret_cast<ConcreteProperty<T>*>( prop_iter->second );
#endif

		c_prop->set_value( value );
	}
}

template <class T>
const T* Message::find_property( HashValue id ) const {
	PropertyMap::const_iterator prop_iter = m_properties.find( id );

	if( prop_iter != m_properties.end() ) {
#ifndef NDEBUG
		const ConcreteProperty<T>* c_prop = dynamic_cast<const ConcreteProperty<T>*>(
			prop_iter->second
		);
		assert( c_prop != nullptr && "Property found but type mismatched." );

		return &c_prop->get_value();
#else
		return &(reinterpret_cast<const ConcreteProperty<T>*>( prop_iter->second )->get_value());
#endif
	}
	else {
		return nullptr;
	}
}

}
