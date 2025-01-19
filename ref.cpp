#include "ref.hpp"
#include "eval_stack.hpp"

#include <string>

namespace lc {

enum {
k_table,
k_id,
k_max };

string id(term_ref t) {
return { .p = get_ptr(t.p, k_id) }; }

static bool prt(term &t, int &pr, bool &rm, print_stack &s, std::ostream &out) {
term_ref const u = { .p = t.p };
out << text(id(u));
return false; }

static bool eval(term &t, term &result, eval_stack s, record &o) {
term_ref const u = { .p = t.p };
bool ok = false;
for (auto [k, v] : o) {
  if (text(k) == text(id(u))) {
    ok = true;
    t = v;
    break; } }
if (ok) { return true; }
throw std::string{ "Undefined reference." }; }

static term apply(term l, term r, record o) {
throw new std::string{ "Not a function" }; }

static term_table tab = { prt, eval, apply };

term_ref::operator term() const { return { .p = p }; }

term_ref new_ref(string id) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field<term_table *>(p, k_table, 0, &tab);
set_field(p, k_id, id.p);
return { .p = p }; }

}