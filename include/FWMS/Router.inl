namespace ms {

template <class T>
T& Router::create_reader() {
	T* reader = new T;
	m_readers.push_back( reader );

	return *reader;
}

}
