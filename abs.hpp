#ifndef GCPP_ABS_HPP
#define GCPP_ABS_HPP

#include "gc.hpp"
#include "string.hpp"
#include "term.hpp"

namespace lc {

struct term_abs { gc::ptr p;
term_abs(gc::ptr &&);
term_abs(term &&);
operator term() &&; };

term_abs new_abs(string const &parameter, term const &body);
string parameter(term_abs const &t);
term body(term_abs const &t);

}

#endif