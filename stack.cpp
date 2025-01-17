#include "stack.hpp"

namespace lc {

stack new_stack() {
return { .p = gc::alloc() }; }

void push(stack t, captures c) {
push_field(t.p, -1, reinterpret_cast<gc::value>(c.t.p));
push_field(t.p, -1, reinterpret_cast<gc::value>(c.o.p)); }

captures top(stack t) {
gc::size n = get_size(t.p);
return {
  .t = { .p = reinterpret_cast<gc::ptr>(get_value(t.p, n - 2)) },
  .o = { .p = reinterpret_cast<gc::ptr>(get_value(t.p, n - 1)) } }; }

void pop(stack t) {
pop_field(t.p);
pop_field(t.p); }

bool empty(stack t) {
return get_size(t.p) == 0; }

}