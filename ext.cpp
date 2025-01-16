#include "ext.hpp"

namespace lc {

enum {
k_kind,
k_defs,
k_body,
k_max };

term_ext::operator term() const { return { .p = p }; }

term_ext new_ext(record defs, term body) {
gc::cell *p = gc::alloc();
p->fields.resize(k_max);
p->fields[k_kind] = { .value = ext, .type = 1 };
p->fields[k_defs] = { .value = reinterpret_cast<size_t>(defs.p), .type = 0 };
p->fields[k_body] = { .value = reinterpret_cast<size_t>(body.p), .type = 0 };
return { .p = p }; }

record defs(term_ext t) {
return { .p = reinterpret_cast<gc::cell *>(t.p->fields[k_defs].value) }; }

term body(term_ext t) {
return { .p = reinterpret_cast<gc::cell *>(t.p->fields[k_body].value) }; }

}