#include "evaluate.hpp"
#include "microgc/gc.hpp"
#include "print.hpp"
#include "read.hpp"
#include "scanner.hpp"
#include "tokenizer.hpp"

#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

int main(int argc, char const **argv) {
try {
  std::string input;
  for (int i = 1; i < argc; i++) {
    input = argv[i]; }
  if (input == "") {
    throw std::string{ "No input file specified." }; }
  gc::set_cleanup(0, [](size_t) -> void {});
  gc::set_cleanup(1, [](size_t x) -> void { free(reinterpret_cast<void *>(x)); });
  std::ifstream in{ input };
  if (!in) {
    throw std::string{ "Unable to open input file for reading." }; }
  using isbi = std::istreambuf_iterator<char>;
  std::string text{ isbi{ in }, isbi{} };
  txt::scanner_t s = txt::scanner(text, input);
  txt::tokenizer_t tk = txt::tokenizer(s);
  lc::print(std::cout, evaluate(lc::read(tk)));
  gc::set_root(nullptr);
  gc::cycle();
  return 0; }
catch (std::string const &e) {
  std::cerr << e;
  return 1; } }