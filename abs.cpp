#include "abs.hpp"
#include "ext.hpp"
#include "stack.hpp"
#include "record.hpp"

namespace lc {

enum {
k_kind,
k_evaluator,
k_parameter,
k_body,
k_max };

static bool eval(term &t, term &result, stack s, record &o) {
term_abs const u = { .p = t.p };
record const d = new_record();
for (auto const [k, v] : o) {
  if (text(k) != text(parameter(u))) {
    set(d, k, v); } }
result = new_abs(parameter(u), new_ext(d, body(u)));
return false; }

term_abs::operator term() const { return { .p = p }; }

term_abs new_abs(string parameter, term body) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_kind, 0, abs);
set_field(p, k_evaluator, 0, eval);
set_field(p, k_parameter, parameter.p);
set_field(p, k_body, body.p);
return { .p = p }; }

string parameter(term_abs t) {
return { .p = get_ptr(t.p, k_parameter) }; }

term body(term_abs t) {
return { .p = get_ptr(t.p, k_body) }; }

}