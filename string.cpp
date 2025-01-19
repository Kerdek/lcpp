#include "string.hpp"

#include <cstring>

namespace lc {

enum {
k_buf,
k_begin,
k_end,
k_max };

string new_string(stringbuf buf, size_t begin, size_t end) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_buf, buf.p);
set_field(p, k_begin, 0, begin);
set_field(p, k_end, 0, k_end);
return { .p = p }; }

stringbuf buf(string s) {
return { .p = get_ptr(s.p, k_buf) }; }

size_t begin(string s) {
return get_value(s.p, k_begin); }

size_t end(string s) {
return get_value(s.p, k_end); }

std::string_view text(string s) {
char const *const p = data(buf(s));
return { p + begin(s), p + end(s) }; }

}