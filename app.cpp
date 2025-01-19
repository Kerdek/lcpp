#include "app.hpp"
#include "abs.hpp"
#include "ext.hpp"
#include "eval_stack.hpp"
#include "term.hpp"

namespace lc {

enum {
k_table,
k_lhs,
k_rhs,
k_max };

term lhs(term_app t) {
return { .p = get_ptr(t.p, k_lhs) }; }

term rhs(term_app t) {
return { .p = get_ptr(t.p, k_rhs) }; }

static bool prt(term &t, int &pr, bool &rm, print_stack &s, std::ostream &out) {
term_app const u = { .p = t.p };
if (pr > 0) out << "(";
s.push({ .t = rhs(u), .pr = pr, .rm = rm, .f = [](term xt, term &t, int &pr, bool &rm, print_stack &s, std::ostream &out) -> bool {
  out << " ";
  s.push({ .t = t, .pr = pr, .rm = rm, .f = [](term xt, term &t, int &pr, bool &rm, print_stack &s, std::ostream &out) -> bool {
    if (pr > 0) out << ")";
    return false; } });
  t = xt;
  rm = pr > 0 || rm;
  pr = 1;
  return true;
}});
t = lhs(u);
pr = 0;
rm = false;
return true;}

static bool eval(term &t, term &result, eval_stack s, record &o) {
term_app const u = { .p = t.p };
push(s, { .t = u, .o = o, .f = [](term xt, term &t, term &result, record &o) -> bool {
  term_app const u = { .p = xt.p };
  term_table *const e = table(result);
  t = e->apply(result, rhs(u), o);
  return true; } });
t = lhs(u);
return true; }

static term apply(term l, term r, record o) {
throw new std::string{ "Not a function" }; }

static term_table tab = { prt, eval, apply };

term_app::operator term() const { return { .p = p }; }

term_app new_app(term lhs, term rhs) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field<term_table *>(p, k_table, 0, &tab);
set_field(p, k_lhs, lhs.p);
set_field(p, k_rhs, rhs.p);
return { .p = p }; }

}