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

struct term_table {
  bool (*evaluate)(term &t, term &result, stack s, record &o); };

term_kind kind(term t);
term_table *table(term t);

}

#endif