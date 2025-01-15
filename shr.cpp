#include "shr.hpp"

namespace lc {

enum {
k_kind,
k_ptr,
k_max };

term_shr::term_shr() : p() { }
term_shr::term_shr(gc::ptr &&p) : p(std::move(p)) { }
term_shr::term_shr(term &&t) : p(std::move(t.p)) { }
term_shr::operator term() && { return std::move(p); }

term_shr new_shr(term const &ptr) {
gc::ptr p = gc::alloc();
p.i->fields.resize(k_max);
p.i->fields[k_kind] = { .value = shr, .type = 1 };
p.i->fields[k_ptr] = { .value = ptr.p, .type = 0 };
return p; }

term ptr(term_shr const &t) {
return gc::ptr(t.p.i->fields[k_ptr].value); }

void set_ptr(term_shr const &t, term const &v) {
t.p.i->fields[k_ptr].value = v.p; } }