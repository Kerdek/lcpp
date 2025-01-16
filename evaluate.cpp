#include "evaluate.hpp"

#include "abs.hpp"
#include "app.hpp"
#include "ext.hpp"
#include "gc.hpp"
#include "ref.hpp"
#include "shr.hpp"
#include "stack.hpp"

#include <string>
#include <cstring>

namespace lc {

term evaluate(term t) {
record o = new_record();
stack const s = new_stack();
term result;
gc::set_root(s.p);
for (;;) {
push(s, { .t = t, .o = o });
gc::help();
pop(s);
term_kind const k = kind(t);
if (k == abs) {
  term_abs const u = { .p = t.p };
  record const d = new_record();
  for (auto const [k, v] : o) {
    if (text(k) != text(parameter(u))) {
      set(d, k, v); } }
  result = new_abs(parameter(u), new_ext(d, body(u))); }
else if (k == app) {
  term_app const u = { .p = t.p };
  push(s, { .t = std::move(u), .o = o });
  t = lhs(u);
  continue; }
else if (k == ref) {
  term_ref const u = { .p = t.p };
  bool ok = false;
  for (auto [k, v] : o) {
    if (text(k) == text(id(u))) {
      ok = true;
      t = std::move(v);
      break; } }
  if (ok) { continue; }
  throw std::string{ "Undefined reference." }; }
else if (k == ext) {
  term_ext const u = { .p = t.p };
  record const d = new_record();
  for (auto const [k, v] : o) {
    set(d, k, v); }
  for (auto const [k, v] : defs(u)) {
    set(d, k, v); }
  o = d;
  t = body(u);
  continue; }
else if (k == shr) {
  term_shr const u = { .p = t.p };
  push(s, { .t = std::move(u), .o = o });
  o = new_record();
  t = ptr(u);
  continue; }
else {
  throw std::string{ "Evaluate missed a case." }; }
for (;;) {
if (empty(s)) {
  return result; }
captures const x = top(s);
pop(s);
o = x.o;
if (kind(x.t) == app) {
  term_app const u = { .p = x.t.p };
  term_kind const k = kind(result);
  if (k == abs) {
    term_abs const dxu = { .p = result.p };
    record const d = new_record();
    set(d, parameter(dxu), new_shr(new_ext(o, rhs(u))));
    t = new_ext(d, body(dxu));
    break; }
  else {
    throw std::string{ "Expected a function." }; } }
else if (kind(x.t) == shr) {
  term_shr const u = { .p = x.t.p };
  set_ptr(u, result); }
else {
  throw std::string{ "Missed a case." }; } } } }

}
