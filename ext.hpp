#ifndef GCPP_EXT_HPP
#define GCPP_EXT_HPP

#include "record.hpp"
#include "gc.hpp"
#include "term.hpp"

namespace lc {

struct term_ext { gc::cell *p;
operator term() const; };

term_ext new_ext(record defs, term body);
record defs(term_ext t);
term body(term_ext t);

}

#endif