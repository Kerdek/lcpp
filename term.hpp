#ifndef GCPP_TERM_HPP
#define GCPP_TERM_HPP

#include "MicroGC/gc.hpp"

#include <iostream>
#include <stack>

namespace lc {

struct term { gc::ptr p; };


struct record;
struct eval_stack;

struct print_frame;
using print_stack = std::stack<print_frame>;

struct print_frame {
term t;
int pr;
bool rm;
bool (*f)(term xt, term &t, int &pr, bool &rm, print_stack &s, std::ostream &out); };

struct term_table {
  bool (*print)(term &t, int &pr, bool &rm, print_stack &s, std::ostream &out);
  bool (*evaluate)(term &t, term &result, eval_stack s, record &o);
  term (*apply)(term l, term r, record o); };

term_table *table(term t);

}

#endif