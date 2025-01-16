#include "print.hpp"
#include "abs.hpp"
#include "app.hpp"
#include "ref.hpp"
#include "ext.hpp"
#include "shr.hpp"

#include <ostream>

namespace lc {

static void print_term(std::ostream &out, term t, int pr, bool rm);

static void print_parameters(std::ostream &out, term t) {
term_kind const k = kind(t);
if (k == abs) {
  term_abs const u = { .p = t.p };
  out << " " << text(parameter(u));
  print_parameters(out, body(u));}
else {
  out << ".";
  print_term(out, t, 0, true); } }

static void print_term(std::ostream &out, term t, int pr, bool rm) {
term_kind const k = kind(t);
if (k == abs) {
  term_abs const u = { .p = t.p };
  bool const parens = !rm;
  if (parens) out << "(";
  out << "\\" << text(parameter(u));
  print_parameters(out, body(u));
  if (parens) out << ")"; }
else if (k == app) {
  term_app const u = { .p = t.p };
  bool const parens = pr > 0;
  if (parens) out << "(";
  print_term(out, lhs(u), 0, false);
  out << " ";
  print_term(out, rhs(u), 1, parens || rm);
  if (parens) out << ")"; }
else if (k == ref) {
  term_ref const u = { .p = t.p };
  out << text(id(u)); }
else if (k == ext) {
  term_ext const u = { .p = t.p };
  print_term(out, body(u), pr, rm); }
else if (k == shr) {
  term_shr const u = { .p = t.p };
  out << "<shared>"; }
else {
  throw std::string{ "Print missed a case." }; } }

void print(std::ostream &out, term t) {
print_term(out, t, 0, true); }

}