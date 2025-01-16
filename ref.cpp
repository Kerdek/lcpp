#include "ref.hpp"

namespace lc {

enum {
k_kind,
k_id,
k_max };

term_ref::operator term() const { return { .p = p }; }

term_ref new_ref(string id) {
gc::cell *p = gc::alloc();
p->fields.resize(k_max);
p->fields[k_kind] = { .value = ref, .type = 1 };
p->fields[k_id] = { .value = reinterpret_cast<size_t>(id.p), .type = 0 };
return { .p = p }; }

string id(term_ref t) {
return { .p = reinterpret_cast<gc::cell *>(t.p->fields[k_id].value) }; }

}