#ifndef GCPP_APP_HPP
#define GCPP_APP_HPP

#include "gc.hpp"
#include "term.hpp"

namespace lc {

struct term_app { gc::cell *p;
operator term() const; };

term_app new_app(term lhs, term rhs);
term lhs(term_app t);
term rhs(term_app t);

}

#endif