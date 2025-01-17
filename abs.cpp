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
set_field(p, k_parameter, parameter.p);
set_field(p, k_body, body.p);
return { .p = p }; }

string parameter(term_abs t) {
return { .p = get_value<gc::ptr>(t.p, k_parameter) }; }

term body(term_abs t) {
return { .p = get_value<gc::ptr>(t.p, k_body) }; }

}