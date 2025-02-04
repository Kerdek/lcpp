#ifndef GCPP_EXT_HPP
#define GCPP_EXT_HPP

#include "record.hpp"
#include "term.hpp"

namespace lc {

struct term_ext { gc::ptr p;
operator term() const; };

term_ext new_ext(record defs, term body);

}

#endif