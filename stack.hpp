#ifndef LCPP_STACK_HPP
#define LCPP_STACK_HPP

#include "record.hpp"
#include "term.hpp"

namespace lc {

struct captures { term t; record o; };

struct stack { gc::cell *p;
stack(gc::cell *p);
stack(stack &&); };

stack new_stack();
void push(stack const &t, captures c);
captures top(stack const &t);
void pop(stack const &t);
bool empty(stack const &t);


}

#endif