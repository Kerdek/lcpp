#include "stringbuf.hpp"

namespace lc {

enum {
k_data,
k_max };

stringbuf::stringbuf(gc::cell *p) : p(p) { }

stringbuf new_stringbuf(char const *data) {
gc::cell *p = gc::alloc();
p->fields.resize(k_max);
p->fields[k_data] = { .value = reinterpret_cast<size_t>(data), .type = 2 };
return p; }

char const *data(stringbuf s) {
return reinterpret_cast<char const *>(s.p->fields[k_data].value); }

}