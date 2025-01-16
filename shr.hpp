#ifndef GCPP_SHR_HPP
#define GCPP_SHR_HPP

#include "gc.hpp"
#include "term.hpp"

namespace lc {

struct term_shr { gc::cell *p;
operator term() const; };

term_shr new_shr(term ptr);
term ptr(term_shr t);
void set_ptr(term_shr t, term v);

}

#endif