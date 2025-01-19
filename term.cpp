#include "term.hpp"

namespace lc {

enum {
k_kind,
k_table };

term_kind kind(term t) {
return get_value<term_kind>(t.p, k_kind); }

term_table *table(term t) {
return get_value<term_table *>(t.p, k_table); }

}