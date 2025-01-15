#ifndef GCPP_TERM_HPP
#define GCPP_TERM_HPP

#include "gc.hpp"

namespace lc {

enum term_kind {
abs,
app,
ref,
ext,
shr };

struct term { gc::ptr p;
term();
term(gc::ptr &&p);
operator bool() const; };

term_kind kind(term const &t);

}

#endif