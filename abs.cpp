#include "abs.hpp"

namespace lc {

enum {
k_kind,
k_parameter,
k_body,
k_max };

term_abs::operator term() const { return { .p = p }; }

term_abs new_abs(string parameter, term body) {
gc::cell *p = gc::alloc();
p->fields.resize(k_max);
p->fields[k_kind] = { .value = abs, .type = 1 };
p->fields[k_parameter] = { .value = reinterpret_cast<size_t>(parameter.p), .type = 0 };
p->fields[k_body] = { .value = reinterpret_cast<size_t>(body.p), .type = 0 };
return { .p = p }; }

string parameter(term_abs t) {
return { .p = reinterpret_cast<gc::cell *>(t.p->fields[k_parameter].value) }; }

term body(term_abs t) {
return { .p = reinterpret_cast<gc::cell *>(t.p->fields[k_body].value) }; }

}