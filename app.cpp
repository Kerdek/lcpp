#include "app.hpp"
#include "term.hpp"

namespace lc {

enum {
k_kind,
k_lhs,
k_rhs,
k_max };

term_app::operator term() const { return { .p = p }; }

term_app new_app(term lhs, term rhs) {
gc::cell *p = gc::alloc();
p->fields.resize(k_max);
p->fields[k_kind] = { .value = app, .type = 1 };
p->fields[k_lhs] = { .value = reinterpret_cast<size_t>(lhs.p), .type = 0 };
p->fields[k_rhs] = { .value = reinterpret_cast<size_t>(rhs.p), .type = 0 };
return { .p = p }; }

term lhs(term_app t) {
return { .p = reinterpret_cast<gc::cell *>(t.p->fields[k_lhs].value) }; }

term rhs(term_app t) {
return { .p = reinterpret_cast<gc::cell *>(t.p->fields[k_rhs].value) }; }

}