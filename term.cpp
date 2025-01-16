#include "term.hpp"

namespace lc {

enum {
k_kind };

term_kind kind(term t) {
return static_cast<term_kind>(t.p->fields[k_kind].value); }

}