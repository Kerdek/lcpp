#ifndef GCPP_RECORD_HPP
#define GCPP_RECORD_HPP

#include "gc.hpp"
#include "shr.hpp"
#include "string.hpp"

namespace lc {

struct record { gc::ptr p;
record(gc::ptr &&p); };

struct record_iter {
std::vector<gc::field>::iterator i;
std::pair<string, term_shr> operator*();
bool operator!=(record_iter);
record_iter &operator++(); };

record new_record();

record_iter begin(record const &d);
record_iter end(record const &d);

term_shr get(record const &d, string const &f);
void set(record const &d, string const &f, term_shr const &v);

}

#endif