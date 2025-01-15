#include "tokenizer.hpp"

namespace txt {

void ws(tokenizer_t &t) {
for (;;) {
  char const c = get(t.s, 0);
  if (c == ' ' || c == '\t' || c == '\n') {
    skip(t.s, 1); }
  else {
    return; } } }

void classify(tokenizer_t &t) {
char const c = get(t.s, 0);
if (c == 0) {
  t.k = tk_eof; return; }
if (c == '(') { t.k = tk_lparen; t.t = "("; return; }
if (c == ')') { t.k = tk_rparen; t.t = ")"; return; }
if (c == '\\') { t.k = tk_rsolidus; t.t = "\\"; return; }
if (c == '.') { t.k = tk_dot; t.t = "."; return; }
if (std::isalpha(c) || c == '_') {
  std::string id;
  int i = 0;
  while (std::isalnum(get(t.s, i)) || get(t.s, i) == '_') {
    id.push_back(get(t.s, i));
    i++; }
  t.k = tk_ident; t.t = id; return; }
throw std::string{ "Unrecognized character sequence." }; }

void skip(tokenizer_t &t) {
if (t.k == tk_eof) {
  return; }
skip(t.s, t.t.size());
ws(t);
classify(t); }

tokenizer_t tokenizer(scanner_t &s) {
tokenizer_t t{ .s = s };
classify(t);
return t; }

std::optional<std::pair<token_kind, std::string>> take(tokenizer_t &t, token_kind k) {
if (t.k == k) {
  auto const r = std::make_pair(t.k, t.t);
  skip(t);
  return r; }
return std::nullopt; }

token_kind peek(tokenizer_t &t) {
return t.k; }

int line(tokenizer_t &t) {
return line(t.s); }

int col(tokenizer_t &t) {
return col(t.s); }

}