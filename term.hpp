#ifndef GCPP_TERM_HPP
#define GCPP_TERM_HPP

#include "MicroGC/gc.hpp"

namespace lc {

enum term_kind {
abs,
app,
ref,
ext,
shr };

struct term { gc::ptr p; };

term_kind kind(term t);

}

#endif