#include "print.hpp"

#include <ostream>
#include <stack>

namespace lc {

void print(std::ostream &out, term t) {
std::stack<print_frame> s;
int pr = 0; bool rm = true;
for (;;) {
  term_table *e = table(t);
  if (e->print(t, pr, rm, s, out)) {
    continue; }
  for (;;) {
    if (empty(s)) {
      return; }
    print_frame const x = s.top();
    s.pop();
    pr = x.pr; rm = x.rm;
    if (x.f(x.t, t, pr, rm, s, out)) {
      break; } } } }

}