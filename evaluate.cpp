#include "evaluate.hpp"
#include "stack.hpp"
#include "record.hpp"
#include "term.hpp"

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
term_table *e = table(t);
if (e->evaluate(t, result, s, o)) {
  continue; }
for (;;) {
if (empty(s)) {
  return result; }
captures const x = top(s);
pop(s);
o = x.o;
if (x.f(x.t, t, result, o)) { break; } } } }

}
