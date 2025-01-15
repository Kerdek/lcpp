#include "ref.hpp"

namespace lc {

enum {
k_kind,
k_id,
k_max };

term_ref::term_ref(gc::ptr &&p) : p(std::move(p)) { }
term_ref::term_ref(term &&t) : p(std::move(t.p)) { }
term_ref::operator term() && { return std::move(p); }

term_ref new_ref(string const &id) {
gc::ptr p = gc::alloc();
p.i->fields.resize(k_max);
p.i->fields[k_kind] = { .value = ref, .type = 1 };
p.i->fields[k_id] = { .value = id.p, .type = 0 };
return term_ref(std::move(p)); }

string id(term_ref const &t) {
return gc::ptr(t.p.i->fields[k_id].value); }

}