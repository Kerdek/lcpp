#include "scanner.hpp"

namespace txt {

scanner_t scanner(std::string const &text, std::string const &file) {
scanner_t s { .text = text, .off = 0, .file = file, .line = 1, .col = 1 };
return s; }

char get(scanner_t &s, size_t i) {
return s.text[s.off + i]; }

int line(scanner_t &s) {
return s.line; }

int col(scanner_t &s) {
return s.col; }

void skip(scanner_t &s, size_t n) {
while (n--) {
  if (get(s, 0) == '\n') {
    s.line++;
    s.col = 1; }
  else {
    s.col++; }
  s.off++; } }

}