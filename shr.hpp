#ifndef GCPP_SHR_HPP
#define GCPP_SHR_HPP

#include "gc.hpp"
#include "term.hpp"

namespace lc {

struct term_shr { gc::ptr p;
term_shr();
term_shr(gc::ptr &&p);
term_shr(term &&);
operator term() &&; };

term_shr new_shr(term const &ptr);
term ptr(term_shr const &t);
void set_ptr(term_shr const &t, term const &v);

}

#endif