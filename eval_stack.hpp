#ifndef LCPP_EVAL_STACK_HPP
#define LCPP_EVAL_STACK_HPP

#include "record.hpp"
#include "term.hpp"

namespace lc {

using eval_stem = bool (*)(term xt, term &t, term &result, record &o);
struct eval_frame { term t; record o; bool (*f)(term xt, term &t, term &result, record &o); };

struct eval_stack { gc::ptr p; };

eval_stack new_eval_stack();
void push(eval_stack t, eval_frame c);
eval_frame top(eval_stack t);
void pop(eval_stack t);
bool empty(eval_stack t);


}

#endif