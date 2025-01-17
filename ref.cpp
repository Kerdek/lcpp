#include "ref.hpp"

namespace lc {

enum {
k_kind,
k_id,
k_max };

term_ref::operator term() const { return { .p = p }; }

term_ref new_ref(string id) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_kind, 0, ref);
set_field(p, k_id, -1, reinterpret_cast<gc::value>(id.p));
return { .p = p }; }

string id(term_ref t) {
return { .p = reinterpret_cast<gc::ptr>(get_value(t.p, k_id)) }; }

}