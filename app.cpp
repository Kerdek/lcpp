#include "app.hpp"
#include "abs.hpp"
#include "ext.hpp"
#include "stack.hpp"
#include "term.hpp"

#include <string>

namespace lc {

enum {
k_kind,
k_evaluator,
k_lhs,
k_rhs,
k_max };

static bool stem_app(term xt, term &t, term &result, record &o) {
term_app const u = { .p = xt.p };
term_kind const k = kind(result);
if (k == abs) {
  term_abs const dxu = { .p = result.p };
  record const d = new_record();
  set(d, parameter(dxu), new_shr(new_ext(o, rhs(u))));
  t = new_ext(d, body(dxu));
  return true; }
else {
  throw std::string{ "Expected a function." }; } }

static bool eval(term &t, term &result, stack s, record &o) {
term_app const u = { .p = t.p };
push(s, { .t = u, .o = o, .f = stem_app });
t = lhs(u);
return true; }

term_app::operator term() const { return { .p = p }; }

term_app new_app(term lhs, term rhs) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_kind, 0, app);
set_field(p, k_evaluator, 0, eval);
set_field(p, k_lhs, lhs.p);
set_field(p, k_rhs, rhs.p);
return { .p = p }; }

term lhs(term_app t) {
return { .p = get_ptr(t.p, k_lhs) }; }

term rhs(term_app t) {
return { .p = get_ptr(t.p, k_rhs) }; }

}