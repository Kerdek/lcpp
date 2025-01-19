#ifndef GCPP_TERM_HPP
#define GCPP_TERM_HPP

#include "MicroGC/gc.hpp"

namespace lc {

struct record;
struct stack;

enum term_kind {
abs,
app,
ref,
ext,
shr };

struct term { gc::ptr p; };

term_kind kind(term t);
bool (*evaluator(term t))(term &t, term &result, stack s, record &o);

}

#endif