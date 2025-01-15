#ifndef GCPP_STRINGBUF_HPP
#define GCPP_STRINGBUF_HPP

#include "gc.hpp"

namespace lc {

struct stringbuf { gc::ptr p;
stringbuf(gc::ptr &&p); };

stringbuf new_stringbuf(const char *data);
const char *data(stringbuf const &s);

}

#endif