#include "term.hpp"

namespace lc {

enum {
k_table };

term_table *table(term t) {
return get_value<term_table *>(t.p, k_table); }

}