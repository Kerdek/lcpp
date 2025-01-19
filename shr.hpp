#ifndef GCPP_SHR_HPP
#define GCPP_SHR_HPP

#include "term.hpp"

namespace lc {

struct term_shr { gc::ptr p;
operator term() const; };

term_shr new_shr(term ptr);

}

#endif