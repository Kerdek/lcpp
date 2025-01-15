#include "string.hpp"
#include "gc.hpp"

#include <cstring>

namespace lc {

enum {
k_buf,
k_begin,
k_end,
k_max };

string::string(gc::ptr &&p) : p(std::move(p)) { }

string new_string(stringbuf buf, size_t begin, size_t end) {
gc::ptr p = gc::alloc();
p.i->fields.resize(k_max);
p.i->fields[k_buf] = { .value = reinterpret_cast<size_t>(buf.p.i), .type = 0 };
p.i->fields[k_begin] = { .value = begin, .type = 1 };
p.i->fields[k_end] = { .value = end, .type = 1 };
return p; }

stringbuf buf(string const &s) {
return gc::ptr(reinterpret_cast<gc::cell *>(s.p.i->fields[k_buf].value)); }

size_t begin(string const &s) {
return s.p.i->fields[k_begin].value; }

size_t end(string const &s) {
return s.p.i->fields[k_end].value; }

std::string_view text(string const &s) {
char const *const p = data(buf(s));
return { p + begin(s), p + end(s) }; }

}