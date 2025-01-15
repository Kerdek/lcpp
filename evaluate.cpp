#include "evaluate.hpp"

#include "abs.hpp"
#include "app.hpp"
#include "ext.hpp"
#include "ref.hpp"
#include "shr.hpp"

#include <stack>
#include <string>
#include <cstring>
#include <variant>

namespace lc {

struct app_case { term rhs; record o; };
struct shr_case { term_shr shr; record o; };

using stack = std::stack<std::variant<
app_case,
shr_case>>;

struct evaluate_stems {
term &result, &t;
stack &s; record &o;
auto operator()(app_case x) -> bool  {
  o = x.o;
  term_kind const k = kind(result);
  if (k == abs) {
    term_abs const dxu = std::move(result);
    record const d = new_record();
    set(d, parameter(dxu), new_shr(new_ext(o, x.rhs)));
    t = new_ext(d, body(dxu));
    return true; }
  else {
    throw std::string{ "Expected a function." }; } }
auto operator()(shr_case x) -> bool {
  o = x.o;
  set_ptr(x.shr, result);
  return false; } };

term evaluate(term t, record o) {
stack s;
term result;

for (;;) {
gc::help();
term_kind const k = kind(t);
if (k == abs) {
  term_abs const u = std::move(t);
  record const d = new_record();
  for (const auto [k, v] : o) {
    if (text(k) != text(parameter(u))) {
      set(d, k, v); } }
  result = new_abs(parameter(u), new_ext(d, body(u))); }
else if (k == app) {
  term_app const u = std::move(t);
  s.push(app_case{ .rhs = rhs(u), .o = o });
  t = lhs(u);
  continue; }
else if (k == ref) {
  term_ref const u = std::move(t);
  bool ok = false;
  for (auto [k, v] : o) {
    if (text(k) == text(id(u))) {
      ok = true;
      t = std::move(v);
      break; } }
  if (ok) { continue; }
  throw std::string{ "Undefined reference." }; }
else if (k == ext) {
  term_ext const u = std::move(t);
  record const d = new_record();
  for (auto const [k, v] : o) {
    set(d, k, v); }
  for (auto const [k, v] : defs(u)) {
    set(d, k, v); }
  o = d;
  t = body(u);
  continue; }
else if (k == shr) {
  term_shr u = std::move(t);
  s.push(shr_case{ .shr = u, .o = o });
  o = new_record();
  t = ptr(u);
  continue; }
else {
  throw std::string{ "Evaluate missed a case." }; }
for (;;) {
if (s.empty()) {
  return result; }
auto const v = s.top();
s.pop();
if (std::visit(evaluate_stems{ result, t, s, o }, v)) {
  break; }; } } }

}
