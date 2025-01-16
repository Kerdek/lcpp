#ifndef GCPP_ABS_HPP
#define GCPP_ABS_HPP

#include "gc.hpp"
#include "string.hpp"
#include "term.hpp"

namespace lc {

struct term_abs { gc::cell *p;
operator term() const; };

term_abs new_abs(string parameter, term body);
string parameter(term_abs t);
term body(term_abs t);

}

#endif