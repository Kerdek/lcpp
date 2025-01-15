#include "record.hpp"
#include "gc.hpp"

#include <string>

namespace lc {

record::record(gc::ptr &&p) : p(std::move(p)) { }

std::pair<string, term_shr> record_iter::operator*() {
gc::field const k = *i;
gc::field const v = *(i + 1);
return {
  gc::ptr(k.value),
  gc::ptr(v.value) }; }

bool record_iter::operator!=(record_iter x) {
return i != x.i; }

record_iter &record_iter::operator++() {
i += 2;
return *this; }

record new_record() {
return gc::alloc(); }

record_iter begin(record const &d) {
return { .i = begin(d.p.i->fields) }; }

record_iter end(record const &d) {
return { .i = end(d.p.i->fields) }; }

term_shr get(record const &d, string const &f) {
for (int i = 0; i < d.p.i->fields.size(); i += 2) {
  gc::field const x = d.p.i->fields[i];
  if (text(f) == text(string(reinterpret_cast<gc::cell *>(x.value)))) {
    return term_shr(reinterpret_cast<gc::cell *>(d.p.i->fields[i + 1].value)); } }
return term_shr(); }

void set(record const &d, string const &f, term_shr const &v) {
for (int i = 0; i < d.p.i->fields.size(); i += 2) {
  gc::field const x = d.p.i->fields[i];
  if (text(f) == text(string(reinterpret_cast<gc::cell *>(x.value)))) {
    d.p.i->fields[i + 1].value = reinterpret_cast<size_t>(v.p.i);
    return; } }
d.p.i->fields.push_back({ .value = reinterpret_cast<size_t>(f.p.i), .type = 0 });
d.p.i->fields.push_back({ .value = reinterpret_cast<size_t>(v.p.i), .type = 0 }); }


}