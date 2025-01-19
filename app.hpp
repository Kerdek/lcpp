#ifndef GCPP_APP_HPP
#define GCPP_APP_HPP

#include "term.hpp"

namespace lc {

struct term_app { gc::ptr p;
operator term() const; };

term_app new_app(term lhs, term rhs);

}

#endif