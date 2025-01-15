#include "abs.hpp"

namespace lc {

enum {
k_kind,
k_parameter,
k_body,
k_max };

term_abs::term_abs(gc::ptr &&p) : p(std::move(p)) { }
term_abs::term_abs(term &&t) : p(std::move(t.p)) { }
term_abs::operator term() && { return std::move(p); }

term_abs new_abs(string const &parameter, term const &body) {
gc::ptr p = gc::alloc();
p.i->fields.resize(k_max);
p.i->fields[k_kind] = { .value = abs, .type = 1 };
p.i->fields[k_parameter] = { .value = parameter.p, .type = 0 };
p.i->fields[k_body] = { .value = body.p, .type = 0 };
return p; }

string parameter(term_abs const &t) {
return gc::ptr(t.p.i->fields[k_parameter].value); }

term body(term_abs const &t) {
return gc::ptr(t.p.i->fields[k_body].value); }

}