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
set_field(p, k_defs, defs.p);
set_field(p, k_body, body.p);
return { .p = p }; }

record defs(term_ext t) {
return { .p = get_value<gc::ptr>(t.p, k_defs) }; }

term body(term_ext t) {
return { .p = get_value<gc::ptr>(t.p, k_body) }; }

}