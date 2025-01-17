#include "app.hpp"
#include "term.hpp"

namespace lc {

enum {
k_kind,
k_lhs,
k_rhs,
k_max };

term_app::operator term() const { return { .p = p }; }

term_app new_app(term lhs, term rhs) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_kind, 0, app);
set_field(p, k_lhs, -1, reinterpret_cast<gc::value>(lhs.p));
set_field(p, k_rhs, -1, reinterpret_cast<gc::value>(rhs.p));
return { .p = p }; }

term lhs(term_app t) {
return { .p = reinterpret_cast<gc::ptr>(get_value(t.p, k_lhs)) }; }

term rhs(term_app t) {
return { .p = reinterpret_cast<gc::ptr>(get_value(t.p, k_rhs)) }; }

}