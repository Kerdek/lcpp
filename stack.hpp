#ifndef LCPP_STACK_HPP
#define LCPP_STACK_HPP

#include "record.hpp"
#include "term.hpp"

namespace lc {

using eval_stem = bool (*)(term xt, term &t, term &result, record &o);
struct captures { term t; record o; bool (*f)(term xt, term &t, term &result, record &o); };

struct stack { gc::ptr p; };

stack new_stack();
void push(stack t, captures c);
captures top(stack t);
void pop(stack t);
bool empty(stack t);


}

#endif