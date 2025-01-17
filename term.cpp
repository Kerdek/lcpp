#include "term.hpp"

namespace lc {

enum {
k_kind };

term_kind kind(term t) {
return static_cast<term_kind>(get_value(t.p, k_kind)); }

}