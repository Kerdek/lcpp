#include "term.hpp"

namespace lc {

enum {
k_kind,
k_evaluator };

term_kind kind(term t) {
return get_value<term_kind>(t.p, k_kind); }

bool (*evaluator(term t))(term &t, term &result, stack s, record &o) {
return get_value<bool (*)(term &t, term &result, stack s, record &o)>(t.p, k_evaluator); }

}