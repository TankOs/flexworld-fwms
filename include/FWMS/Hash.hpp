#pragma once

#include <functional>
#include <string>

namespace ms {

typedef std::size_t HashValue; ///< Hash value type.

extern std::hash<std::string> string_hash; ///< Make hash from string.

}
