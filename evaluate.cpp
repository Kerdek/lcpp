#include "evaluate.hpp"
#include "stack.hpp"
#include "record.hpp"

#include <cstring>

namespace lc {

term evaluate(term t) {
record o = new_record();
stack const s = new_stack();
gc::set_root(s.p);
for (;;) {
push(s, { .t = t, .o = o });
gc::help();
pop(s);
term result;
bool (*const f)(term &t, term &result, stack s, record &o) = evaluator(t);
if (f(t, result, s, o)) {
  continue; }
for (;;) {
if (empty(s)) {
  return result; }
captures const x = top(s);
pop(s);
o = x.o;
if (x.f(x.t, t, result, o)) { break; } } } }

}
