#include "read.hpp"
#include "strclone.hpp"
#include "stringbuf.hpp"
#include "tokenizer.hpp"
#include "abs.hpp"
#include "app.hpp"
#include "ref.hpp"

namespace lc {

static term top(txt::tokenizer_t &in);

static term parameters(txt::tokenizer_t &in, txt::token_kind d) {
if (take(in, d)) {
  return top(in); }
else {
  auto const c = take(in, txt::tk_ident);
  if (!c) { throw txt::add_pos(in, "Expected an identifier."); }
  term const e = parameters(in, d);
  return new_abs(new_string(new_stringbuf(strclone(c->second.data())), 0, c->second.length()), e); } }

static bool juxt_continues(txt::tokenizer_t &in) {
txt::token_kind const k = peek(in);
return
  k == txt::tk_rsolidus ||
  k == txt::tk_lparen ||
  k == txt::tk_ident; }

static term primary(txt::tokenizer_t &in) {
if (take(in, txt::tk_rsolidus)) {
  return parameters(in, txt::tk_dot); }
if (take(in, txt::tk_lparen)) {
  term const e = top(in);
  if (!take(in, txt::tk_rparen)) {
    throw txt::add_pos(in, "Expected `)`."); }
  return e; }
auto const ci = take(in, txt::tk_ident);
if (ci) {
  return new_ref(new_string(new_stringbuf(strclone(ci->second.data())), 0, ci->second.length())); }
else {
  throw txt::add_pos(in, "Expected an expression."); } }

static term juxt_rhs(txt::tokenizer_t &in, term lhs) {
if (juxt_continues(in)) {
  return juxt_rhs(in, new_app(lhs, primary(in))); }
else {
  return lhs; } }

static term juxt(txt::tokenizer_t &in) {
return juxt_rhs(in, primary(in)); }

static term top(txt::tokenizer_t &in) {
return juxt(in); }

term read(txt::tokenizer_t &in) {
return top(in); }

}