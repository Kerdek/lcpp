#include "shr.hpp"
#include "stack.hpp"

namespace lc {

enum {
k_kind,
k_evaluator,
k_ptr,
k_max };

static bool eval(term &t, term &result, stack s, record &o) {
term_shr const u = { .p = t.p };
push(s, { .t = u, .o = o, .f = [](term xt, term &t, term &result, record &o) {
  term_shr const u = { .p = xt.p };
  set_ptr(u, result);
  return false; } });
o = new_record();
t = ptr(u);
return true; }

static term_table tab = {
eval };

term_shr::operator term() const { return { .p = p }; }

term_shr new_shr(term ptr) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field<term_kind>(p, k_kind, 0, shr);
set_field<term_table *>(p, k_evaluator, 0, &tab);
set_field(p, k_ptr, ptr.p);
return { .p = p }; }

term ptr(term_shr t) {
return { .p = get_ptr(t.p, k_ptr) }; }

void set_ptr(term_shr t, term v) {
set_value(t.p, k_ptr, v.p); } }