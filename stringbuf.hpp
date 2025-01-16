#ifndef GCPP_STRINGBUF_HPP
#define GCPP_STRINGBUF_HPP

#include "gc.hpp"

namespace lc {

struct stringbuf { gc::cell *p;
stringbuf(gc::cell *p); };

stringbuf new_stringbuf(const char *data);
const char *data(stringbuf s);

}

#endif