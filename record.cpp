#include "record.hpp"

namespace lc {

std::pair<string, term_shr> record_iter::operator*() {
return {
  { .p = reinterpret_cast<gc::ptr>(get_value(p, i)) },
  { .p = reinterpret_cast<gc::ptr>(get_value(p, i + 1)) } }; }

bool record_iter::operator!=(record_iter x) {
return i != x.i; }

record_iter &record_iter::operator++() {
i += 2;
return *this; }

record new_record() {
return { .p = gc::alloc() }; }

record_iter begin(record d) {
return { .p = d.p, .i = 0 }; }

record_iter end(record d) {
return { .p = d.p, .i = get_size(d.p) }; }

term_shr get(record d, string f) {
for (size_t i = 0; i < get_size(d.p); i += 2) {
  if (text(f) == text(string(reinterpret_cast<gc::ptr>(get_value(d.p, i))))) {
    return term_shr(reinterpret_cast<gc::ptr>(get_value(d.p, i + 1))); } }
return term_shr(); }

void set(record d, string f, term_shr v) {
for (gc::size i = 0; i < get_size(d.p); i += 2) {
  if (text(f) == text(string(reinterpret_cast<gc::ptr>(get_value(d.p, i))))) {
    set_value(d.p, i + 1, reinterpret_cast<gc::value>(v.p));
    return; } }
push_field(d.p, -1, reinterpret_cast<gc::value>(f.p));
push_field(d.p, -1, reinterpret_cast<gc::value>(v.p)); }

}