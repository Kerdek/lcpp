#ifndef GCPP_STRINGBUF_HPP
#define GCPP_STRINGBUF_HPP

#include "microgc/gc.hpp"

namespace lc {

struct stringbuf { gc::ptr p; };

stringbuf new_stringbuf(const char *data);
const char *data(stringbuf s);

}

#endif