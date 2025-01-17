#include "shr.hpp"

namespace lc {

enum {
k_kind,
k_ptr,
k_max };

term_shr::operator term() const { return { .p = p }; }

term_shr new_shr(term ptr) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_kind, 0, shr);
set_field(p, k_ptr, ptr.p);
return { .p = p }; }

term ptr(term_shr t) {
return { .p = get_value<gc::ptr>(t.p, k_ptr) }; }

void set_ptr(term_shr t, term v) {
set_value(t.p, k_ptr, v.p); } }