#include "app.hpp"
#include "abs.hpp"
#include "ext.hpp"
#include "stack.hpp"
#include "term.hpp"

namespace lc {

enum {
k_kind,
k_table,
k_lhs,
k_rhs,
k_max };

static bool eval(term &t, term &result, stack s, record &o) {
term_app const u = { .p = t.p };
push(s, { .t = u, .o = o, .f = [](term xt, term &t, term &result, record &o) -> bool {
  term_app const u = { .p = xt.p };
  term_abs const dxu = { .p = result.p };
  record const d = new_record();
  set(d, parameter(dxu), new_shr(new_ext(o, rhs(u))));
  t = new_ext(d, body(dxu));
  return true; } });
t = lhs(u);
return true; }

static term_table tab = {
eval };

term_app::operator term() const { return { .p = p }; }

term_app new_app(term lhs, term rhs) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field<term_kind>(p, k_kind, 0, app);
set_field<term_table *>(p, k_table, 0, &tab);
set_field(p, k_lhs, lhs.p);
set_field(p, k_rhs, rhs.p);
return { .p = p }; }

term lhs(term_app t) {
return { .p = get_ptr(t.p, k_lhs) }; }

term rhs(term_app t) {
return { .p = get_ptr(t.p, k_rhs) }; }

}