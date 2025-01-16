#ifndef GCPP_RECORD_HPP
#define GCPP_RECORD_HPP

#include "gc.hpp"
#include "shr.hpp"
#include "string.hpp"

namespace lc {

struct record { gc::cell *p; };

struct record_iter {
std::vector<gc::field>::iterator i;
std::pair<string, term_shr> operator*();
bool operator!=(record_iter);
record_iter &operator++(); };

record new_record();

record_iter begin(record d);
record_iter end(record d);

term_shr get(record d, string f);
void set(record d, string f, term_shr v);

}

#endif