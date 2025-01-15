#ifndef GCPP_TOKENIZER_HPP
#define GCPP_TOKENIZER_HPP

#include "scanner.hpp"

#include <optional>
#include <string>

namespace txt {

enum token_kind {
  tk_eof,
  tk_lparen,
  tk_rparen,
  tk_rsolidus,
  tk_dot,
  tk_ident };

struct tokenizer_t {
scanner_t &s;
token_kind k;
std::string t; };

tokenizer_t tokenizer(scanner_t &s);
std::optional<std::pair<token_kind, std::string>> take(tokenizer_t &t, token_kind k);
token_kind peek(tokenizer_t &t);
std::string file(tokenizer_t &t);
int line(tokenizer_t &t);
int col(tokenizer_t &t);


}

#endif