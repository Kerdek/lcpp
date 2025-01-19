#ifndef GCPP_TERM_HPP
#define GCPP_TERM_HPP

#include "MicroGC/gc.hpp"

#include <iostream>
#include <stack>

namespace lc {

enum term_kind {
abs,
app,
ref,
ext,
shr };

struct term;
struct print_frame;

struct record;
struct eval_stack;

struct term { gc::ptr p; };

using print_stack = std::stack<print_frame>;

struct print_frame {
term t;
int pr;
bool rm;
bool (*f)(term xt, term &t, int &pr, bool &rm, print_stack &s, std::ostream &out); };

struct term_table {
  bool (*print)(term &t, int &pr, bool &rm, print_stack &s, std::ostream &out);
  bool (*evaluate)(term &t, term &result, eval_stack s, record &o); };

term_kind kind(term t);
term_table *table(term t);

}

#endif