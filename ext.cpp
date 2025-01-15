#include "ext.hpp"

namespace lc {

enum {
k_kind,
k_defs,
k_body,
k_max };

term_ext::term_ext(gc::ptr &&p) : p(std::move(p)) { }
term_ext::term_ext(term &&t) : p(std::move(t.p)) { }
term_ext::operator term() && { return std::move(p); }

term_ext new_ext(record const &defs, term const &body) {
gc::ptr p = gc::alloc();
p.i->fields.resize(k_max);
p.i->fields[k_kind] = { .value = ext, .type = 1 };
p.i->fields[k_defs] = { .value = defs.p, .type = 0 };
p.i->fields[k_body] = { .value = body.p, .type = 0 };
return term_ext(std::move(p)); }

record defs(term_ext const &t) {
return gc::ptr(t.p.i->fields[k_defs].value); }

term body(term_ext const &t) {
return gc::ptr(t.p.i->fields[k_body].value); }

}