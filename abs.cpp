#include "abs.hpp"
#include "ext.hpp"
#include "eval_stack.hpp"
#include "record.hpp"

namespace lc {

enum {
k_table,
k_parameter,
k_body,
k_max };

string parameter(term_abs t) {
return { .p = get_ptr(t.p, k_parameter) }; }

term body(term_abs t) {
return { .p = get_ptr(t.p, k_body) }; }

static bool prt(term &t, int &pr, bool &rm, print_stack &s, std::ostream &out) {
term_abs const u = { .p = t.p };
if (!rm) out << "(";
out << "\\" << text(parameter(u)) << ".";
s.push({ .t = t, .pr = pr, .rm = rm, .f = [](term xt, term &t, int &pr, bool &rm, print_stack &s, std::ostream &out) -> bool {
  if (!rm) out << ")";
  return false; }});
t = body(u);
pr = 0;
rm = true;
return true; }

static bool eval(term &t, term &result, eval_stack s, record &o) {
term_abs const u = { .p = t.p };
record const d = new_record();
for (auto const [k, v] : o) {
  if (text(k) != text(parameter(u))) {
    set(d, k, v); } }
result = new_abs(parameter(u), new_ext(d, body(u)));
return false; }

static term apply(term l, term r, record o) {
term_abs const u = { .p = l.p };
record const d = new_record();
set(d, parameter(u), new_shr(new_ext(o, r)));
return new_ext(d, body(u)); }

static term_table tab = { prt, eval, apply };

term_abs::operator term() const { return { .p = p }; }

term_abs new_abs(string parameter, term body) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field<term_table *>(p, k_table, 0, &tab);
set_field(p, k_parameter, parameter.p);
set_field(p, k_body, body.p);
return { .p = p }; }

}