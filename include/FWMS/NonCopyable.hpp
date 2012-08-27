#pragma once

namespace ms {

/** Non-copyable base class.
 */
class NonCopyable {
	public:
		NonCopyable();

	private:
		NonCopyable( const NonCopyable& );
		const NonCopyable& operator=( const NonCopyable& );
};

}
