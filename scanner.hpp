#ifndef GCPP_SCANNER_HPP
#define GCPP_SCANNER_HPP

#include <string>

namespace txt {

struct scanner_t {
std::string text;
size_t off;
std::string file;
int line, col;  };

scanner_t scanner(std::string const &text, std::string const &file);
char get(scanner_t &s, size_t i);
int line(scanner_t &s);
int col(scanner_t &s);
void skip(scanner_t &s, size_t n);

}

#endif