#pragma once

#include <boost/functional/hash.hpp>

namespace ms {

typedef std::size_t HashValue; ///< Hash value type.

extern boost::hash<std::string> string_hash; ///< Make hash from string.

}
