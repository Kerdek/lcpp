#include "eval_stack.hpp"

namespace lc {

eval_stack new_eval_stack() {
return { .p = gc::alloc() }; }

void push(eval_stack t, eval_frame c) {
push_field(t.p, c.t.p);
push_field(t.p, c.o.p);
push_field(t.p, 0, c.f); }

eval_frame top(eval_stack t) {
gc::size n = get_size(t.p);
return {
  .t = { .p = get_ptr(t.p, n - 3) },
  .o = { .p = get_ptr(t.p, n - 2) },
  .f = get_value<eval_stem>(t.p, n - 1) }; }

void pop(eval_stack t) {
pop_field(t.p);
pop_field(t.p);
pop_field(t.p); }

bool empty(eval_stack t) {
return get_size(t.p) == 0; }

}