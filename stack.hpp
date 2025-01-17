#ifndef LCPP_STACK_HPP
#define LCPP_STACK_HPP

#include "record.hpp"
#include "term.hpp"

namespace lc {

struct captures { term t; record o; };

struct stack { gc::ptr p; };

stack new_stack();
void push(stack t, captures c);
captures top(stack t);
void pop(stack t);
bool empty(stack t);


}

#endif