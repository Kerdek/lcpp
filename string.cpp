#include "string.hpp"
#include "gc.hpp"

#include <cstring>

namespace lc {

enum {
k_buf,
k_begin,
k_end,
k_max };

string new_string(stringbuf buf, size_t begin, size_t end) {
gc::cell *p = gc::alloc();
p->fields.resize(k_max);
p->fields[k_buf] = { .value = reinterpret_cast<size_t>(buf.p), .type = 0 };
p->fields[k_begin] = { .value = begin, .type = 1 };
p->fields[k_end] = { .value = end, .type = 1 };
return { .p = p }; }

stringbuf buf(string s) {
return reinterpret_cast<gc::cell *>(s.p->fields[k_buf].value); }

size_t begin(string s) {
return s.p->fields[k_begin].value; }

size_t end(string s) {
return s.p->fields[k_end].value; }

std::string_view text(string s) {
char const *const p = data(buf(s));
return { p + begin(s), p + end(s) }; }

}