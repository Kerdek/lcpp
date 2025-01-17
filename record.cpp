#include "record.hpp"

namespace lc {

std::pair<string, term_shr> record_iter::operator*() {
return {
  { .p = get_value<gc::ptr>(p, i) },
  { .p = get_value<gc::ptr>(p, i + 1) } }; }

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
  if (text(f) == text(string(get_value<gc::ptr>(d.p, i)))) {
    return term_shr(get_value<gc::ptr>(d.p, i + 1)); } }
return term_shr(); }

void set(record d, string f, term_shr v) {
for (gc::size i = 0; i < get_size(d.p); i += 2) {
  if (text(f) == text(string(get_value<gc::ptr>(d.p, i)))) {
    set_value(d.p, i + 1, v.p);
    return; } }
push_field(d.p, f.p);
push_field(d.p, v.p); }

}