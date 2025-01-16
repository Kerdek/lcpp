#include "record.hpp"
#include "gc.hpp"

#include <string>

namespace lc {

std::pair<string, term_shr> record_iter::operator*() {
gc::field const k = *i;
gc::field const v = *(i + 1);
return {
  { .p = reinterpret_cast<gc::cell *>(k.value) },
  { .p = reinterpret_cast<gc::cell *>(v.value) } }; }

bool record_iter::operator!=(record_iter x) {
return i != x.i; }

record_iter &record_iter::operator++() {
i += 2;
return *this; }

record new_record() {
return { .p = gc::alloc() }; }

record_iter begin(record d) {
return { .i = begin(d.p->fields) }; }

record_iter end(record d) {
return { .i = end(d.p->fields) }; }

term_shr get(record d, string f) {
for (int i = 0; i < d.p->fields.size(); i += 2) {
  gc::field const x = d.p->fields[i];
  if (text(f) == text(string(reinterpret_cast<gc::cell *>(x.value)))) {
    return term_shr(reinterpret_cast<gc::cell *>(d.p->fields[i + 1].value)); } }
return term_shr(); }

void set(record d, string f, term_shr v) {
for (int i = 0; i < d.p->fields.size(); i += 2) {
  gc::field const x = d.p->fields[i];
  if (text(f) == text(string(reinterpret_cast<gc::cell *>(x.value)))) {
    d.p->fields[i + 1].value = reinterpret_cast<size_t>(v.p);
    return; } }
d.p->fields.push_back({ .value = reinterpret_cast<size_t>(f.p), .type = 0 });
d.p->fields.push_back({ .value = reinterpret_cast<size_t>(v.p), .type = 0 }); }


}