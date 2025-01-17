#ifndef GCPP_REF_HPP
#define GCPP_REF_HPP

#include "string.hpp"
#include "term.hpp"

namespace lc {

struct term_ref { gc::cell *p;
operator term() const; };

term_ref new_ref(string id);
string id(term_ref t);

}

#endif