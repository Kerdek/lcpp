#include "stack.hpp"

namespace lc {

stack::stack(gc::cell *p) : p(p) {}
stack::stack(stack &&t) : p(t.p) {}

stack new_stack() {
return gc::alloc(); }

void push(stack const &t, captures c) {
t.p->fields.push_back({ .value = reinterpret_cast<size_t>(c.t.p), .type = 0 });
t.p->fields.push_back({ .value = reinterpret_cast<size_t>(c.o.p), .type = 0 }); }

captures top(stack const &t) {
return {
  reinterpret_cast<gc::cell *>(t.p->fields[t.p->fields.size() - 2].value),
  reinterpret_cast<gc::cell *>(t.p->fields[t.p->fields.size() - 1].value) }; }

void pop(stack const &t) {
t.p->fields.pop_back();
t.p->fields.pop_back(); }

bool empty(stack const &t) {
return t.p->fields.empty(); }

}