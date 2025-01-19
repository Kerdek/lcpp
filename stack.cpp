#include "stack.hpp"

namespace lc {

stack new_stack() {
return { .p = gc::alloc() }; }

void push(stack t, captures c) {
push_field(t.p, c.t.p);
push_field(t.p, c.o.p);
push_field(t.p, 0, c.f); }

captures top(stack t) {
gc::size n = get_size(t.p);
return {
  .t = { .p = get_ptr(t.p, n - 3) },
  .o = { .p = get_ptr(t.p, n - 2) },
  .f = get_value<eval_stem>(t.p, n - 1) }; }

void pop(stack t) {
pop_field(t.p);
pop_field(t.p);
pop_field(t.p); }

bool empty(stack t) {
return get_size(t.p) == 0; }

}