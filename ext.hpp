#ifndef GCPP_EXT_HPP
#define GCPP_EXT_HPP

#include "record.hpp"
#include "gc.hpp"
#include "term.hpp"

namespace lc {

struct term_ext { gc::ptr p;
term_ext(gc::ptr &&);
term_ext(term &&);
operator term() &&; };

term_ext new_ext(record const &defs, term const &body);
record defs(term_ext const &t);
term body(term_ext const &t);

}

#endif