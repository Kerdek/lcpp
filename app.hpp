#ifndef GCPP_APP_HPP
#define GCPP_APP_HPP

#include "gc.hpp"
#include "term.hpp"

namespace lc {

struct term_app { gc::ptr p;
term_app(gc::ptr &&);
term_app(term &&);
operator term() &&; };

term_app new_app(term const &lhs, term const &rhs);
term lhs(term_app const &t);
term rhs(term_app const &t);

}

#endif