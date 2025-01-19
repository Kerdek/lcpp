#include "ref.hpp"
#include "stack.hpp"

#include <string>

namespace lc {

enum {
k_kind,
k_evaluator,
k_id,
k_max };

static bool eval(term &t, term &result, stack s, record &o) {
term_ref const u = { .p = t.p };
bool ok = false;
for (auto [k, v] : o) {
  if (text(k) == text(id(u))) {
    ok = true;
    t = v;
    break; } }
if (ok) { return true; }
throw std::string{ "Undefined reference." }; }

term_ref::operator term() const { return { .p = p }; }

term_ref new_ref(string id) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_kind, 0, ref);
set_field(p, k_evaluator, 0, eval);
set_field(p, k_id, id.p);
return { .p = p }; }

string id(term_ref t) {
return { .p = get_ptr(t.p, k_id) }; }

}