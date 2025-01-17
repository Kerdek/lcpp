#include "term.hpp"

namespace lc {

enum {
k_kind };

term_kind kind(term t) {
return get_value<term_kind>(t.p, k_kind); }

}