#include "ext.hpp"
#include "eval_stack.hpp"
#include "term.hpp"

namespace lc {

enum {
k_kind,
k_table,
k_defs,
k_body,
k_max };

static bool prt(term &t, int &pr, bool &rm, print_stack &s, std::ostream &out) {
term_ext const u = { .p = t.p };
s.push(print_frame{ .t = t, .pr = pr, .rm = rm, .f = [](term xt, term &t, int &pr, bool &rm, print_stack &s, std::ostream &out) -> bool {
  return false; } });
t = body(u);
return true; }

static bool eval(term &t, term &result, eval_stack s, record &o) {
term_ext const u = { .p = t.p };
record const d = new_record();
for (auto const [k, v] : o) {
  set(d, k, v); }
for (auto const [k, v] : defs(u)) {
  set(d, k, v); }
o = d;
t = body(u);
return true; }

static term_table tab = { prt, eval };

term_ext::operator term() const { return { .p = p }; }

term_ext new_ext(record defs, term body) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field<term_kind>(p, k_kind, 0, ext);
set_field<term_table *>(p, k_table, 0, &tab);
set_field(p, k_defs, defs.p);
set_field(p, k_body, body.p);
return { .p = p }; }

record defs(term_ext t) {
return { .p = get_ptr(t.p, k_defs) }; }

term body(term_ext t) {
return { .p = get_ptr(t.p, k_body) }; }

}