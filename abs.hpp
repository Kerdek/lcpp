#ifndef GCPP_ABS_HPP
#define GCPP_ABS_HPP

#include "string.hpp"
#include "term.hpp"

namespace lc {

struct term_abs { gc::ptr p;
operator term() const; };

term_abs new_abs(string parameter, term body);
string parameter(term_abs t);
term body(term_abs t);

}

#endif