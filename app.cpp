#include "app.hpp"
#include "term.hpp"

namespace lc {

enum {
k_kind,
k_lhs,
k_rhs,
k_max };

term_app::term_app(gc::ptr &&p) : p(std::move(p)) { }
term_app::term_app(term &&t) : p(std::move(t.p)) { }
term_app::operator term() && { return std::move(p); }

term_app new_app(term const &lhs, term const &rhs) {
gc::ptr p = gc::alloc();
p.i->fields.resize(k_max);
p.i->fields[k_kind] = { .value = app, .type = 1 };
p.i->fields[k_lhs] = { .value = lhs.p, .type = 0 };
p.i->fields[k_rhs] = { .value = rhs.p, .type = 0 };
return p; }

term lhs(term_app const &t) {
return gc::ptr(t.p.i->fields[k_lhs].value); }

term rhs(term_app const &t) {
return gc::ptr(t.p.i->fields[k_rhs].value); }

}