#include "ext.hpp"

namespace lc {

enum {
k_kind,
k_defs,
k_body,
k_max };

term_ext::operator term() const { return { .p = p }; }

term_ext new_ext(record defs, term body) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_kind, 0, ext);
set_field(p, k_defs, -1, reinterpret_cast<gc::value>(defs.p));
set_field(p, k_body, -1, reinterpret_cast<gc::value>(body.p));
return { .p = p }; }

record defs(term_ext t) {
return { .p = reinterpret_cast<gc::ptr>(get_value(t.p, k_defs)) }; }

term body(term_ext t) {
return { .p = reinterpret_cast<gc::ptr>(get_value(t.p, k_body)) }; }

}