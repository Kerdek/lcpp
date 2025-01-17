#include "stringbuf.hpp"

namespace lc {

enum {
k_data,
k_max };

stringbuf new_stringbuf(char const *data) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_data, 1, reinterpret_cast<gc::value>(data));
return { .p = p }; }

char const *data(stringbuf s) {
return reinterpret_cast<char const *>(get_value(s.p, k_data)); }

}