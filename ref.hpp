#ifndef GCPP_REF_HPP
#define GCPP_REF_HPP

#include "gc.hpp"
#include "string.hpp"
#include "term.hpp"

namespace lc {

struct term_ref { gc::ptr p;
term_ref(gc::ptr &&p);
term_ref(term &&);
operator term() &&; };

term_ref new_ref(string const &id);
string id(term_ref const &t);

}

#endif