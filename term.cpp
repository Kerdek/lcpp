#include "term.hpp"

namespace lc {

enum {
k_kind };

term::term() : p(gc::null) { }
term::term(gc::ptr &&p) : p(std::move(p)) { }
term::operator bool() const {
  return p; }

term_kind kind(term const &t) {
return static_cast<term_kind>(t.p.i->fields[k_kind].value); }

}