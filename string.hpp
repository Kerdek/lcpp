#ifndef GCPP_STRING_HPP
#define GCPP_STRING_HPP

#include "gc.hpp"
#include "stringbuf.hpp"

#include <string_view>

namespace lc {

struct string { gc::ptr p;
string(gc::ptr &&p); };

string new_string(stringbuf buf, size_t begin, size_t end);
string clone_string(char const *p);

stringbuf buf(string const &);
size_t begin(string const &);
size_t end(string const &);

std::string_view text(string const &);

}

#endif