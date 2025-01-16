#include "gc.hpp"

#include <algorithm>
#include <cstring>
#include <stack>
#include <unordered_set>
#include <vector>

namespace gc {

std::vector<cell *> full_range;
std::vector<void (*)(size_t)> cleanups;
cell * root;

void set_cleanup(size_t type, void (*f)(size_t)) {
if (cleanups.size() < type) {
  cleanups.resize(type); }
cleanups[type - 1] = f; }

cell *alloc() {
cell *const p = new cell{ };
full_range.push_back(p);
return p; }

void set_root(cell *p) {
root = p; }

void sweep(cell *c) {
for (const auto f : c->fields) {
if (f.type > 0) {
  cleanups[f.type - 1](f.value); } }
delete c; }

void cycle() {
std::unordered_set<cell *> s;
s.max_load_factor(0.5);
std::stack<cell *> stack;
stack.push(root);
while (!stack.empty()) {
  cell *current = stack.top();
  stack.pop();
  if (s.find(current) != s.end()) {
    continue; }
  s.insert(current);
  for (const auto f : current->fields) {
    if (f.type == 0 && f.value) {
      stack.push(reinterpret_cast<cell *>(f.value)); } } }
const auto pivot = std::partition(full_range.begin(), full_range.end(), [&s](cell *x) -> bool {
  return s.find(x) != s.end(); });
std::for_each(pivot, full_range.end(), sweep);
full_range.erase(pivot, full_range.end()); }

size_t const min_trigger = 16;
size_t trigger = min_trigger;

void help() {
if (full_range.size() > trigger) {
  cycle();
  if (full_range.size() > trigger / 2) {
    trigger *= 2; }
  else if (full_range.size() < trigger / 4 && trigger > min_trigger) {
    trigger /= 2; } } }

}