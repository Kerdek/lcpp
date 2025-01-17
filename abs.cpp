#include "abs.hpp"

namespace lc {

enum {
k_kind,
k_parameter,
k_body,
k_max };

term_abs::operator term() const { return { .p = p }; }

term_abs new_abs(string parameter, term body) {
gc::ptr p = gc::alloc();
resize(p, k_max);
set_field(p, k_kind, 0, abs);
set_field(p, k_parameter, -1, reinterpret_cast<gc::value>(parameter.p));
set_field(p, k_body, -1, reinterpret_cast<gc::value>(body.p));
return { .p = p }; }

string parameter(term_abs t) {
return { .p = reinterpret_cast<gc::ptr>(get_value(t.p, k_parameter)) }; }

term body(term_abs t) {
return { .p = reinterpret_cast<gc::ptr>(get_value(t.p, k_body)) }; }

}