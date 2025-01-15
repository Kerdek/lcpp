#include "stringbuf.hpp"

namespace lc {

enum {
k_data,
k_max };

stringbuf::stringbuf(gc::ptr &&p) : p(std::move(p)) { }

stringbuf new_stringbuf(char const *data) {
gc::ptr p = gc::alloc();
p.i->fields.resize(k_max);
p.i->fields[k_data] = { .value = reinterpret_cast<size_t>(data), .type = 2 };
return stringbuf(std::move(p)); }

char const *data(stringbuf const &s) {
return reinterpret_cast<char const *>(s.p.i->fields[k_data].value); }

}