#ifndef GCPP_STRING_HPP
#define GCPP_STRING_HPP

#include "microgc/gc.hpp"
#include "stringbuf.hpp"

#include <string_view>

namespace lc {

struct string { gc::ptr p; };

string new_string(stringbuf buf, size_t begin, size_t end);

stringbuf buf(string s);
size_t begin(string s);
size_t end(string s);

std::string_view text(string s);

}

#endif