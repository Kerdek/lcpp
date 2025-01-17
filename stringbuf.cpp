#include "stringbuf.hpp"

namespace lc {

enum {
k_data,
k_max };

stringbuf new_stringbuf(char const *data) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_data, 1, data);
return { .p = p }; }

char const *data(stringbuf s) {
return get_value<char const *>(s.p, k_data); }

}