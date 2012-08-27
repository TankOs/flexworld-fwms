#pragma once

#include <boost/functional/hash.hpp>

namespace ms {

typedef std::size_t HashValue;

extern boost::hash<std::string> string_hash;

}
