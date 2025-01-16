#include "shr.hpp"

namespace lc {

enum {
k_kind,
k_ptr,
k_max };

term_shr::operator term() const { return { .p = p }; }

term_shr new_shr(term ptr) {
gc::cell *p = gc::alloc();
p->fields.resize(k_max);
p->fields[k_kind] = { .value = shr, .type = 1 };
p->fields[k_ptr] = { .value = reinterpret_cast<size_t>(ptr.p), .type = 0 };
return { .p = p }; }

term ptr(term_shr t) {
return { .p = reinterpret_cast<gc::cell *>(t.p->fields[k_ptr].value) }; }

void set_ptr(term_shr t, term v) {
t.p->fields[k_ptr].value = reinterpret_cast<size_t>(v.p); } }