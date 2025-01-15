#include "gc.hpp"

#include <algorithm>
#include <cstring>
#include <stack>
#include <unordered_set>
#include <vector>

namespace gc {

std::vector<cell *> full_range;
std::unordered_multiset<cell *> live_range = [](){
  std::unordered_multiset<cell *> t;
  t.max_load_factor(0.5);
  return t; }();

ptr::ptr() : i(0) {}

ptr::ptr(cell *i) : i(i) {
if (i) {
  live_range.insert(this->i); } }

ptr::ptr(size_t i) : i(reinterpret_cast<cell *>(i)) {
if (i) {
  live_range.insert(this->i); } }

ptr::ptr(ptr const &x) : i(x.i) {
if (i) {
  live_range.insert(i); } }

ptr::ptr(ptr &&x) : i(x.i) {
x.i = 0; }

ptr &ptr::operator=(ptr const &x) {
if (i) {
  live_range.erase(live_range.find(i)); }
i = x.i;
if (i) {
  live_range.insert(i); }
return *this; }

ptr &ptr::operator=(ptr &&x) {
if (i) {
  live_range.erase(live_range.find(i)); }
i = x.i;
x.i = 0;
return *this; }

ptr::~ptr() {
if (i) {
  live_range.erase(live_range.find(i)); } }

ptr::operator bool() const {
return i; }

ptr::operator size_t() const {
return reinterpret_cast<size_t>(i); }

ptr const null(nullptr);

std::vector<void (*)(size_t)> cleanups;

void set_cleanup(size_t type, void (*f)(size_t)) {
if (cleanups.size() < type) {
  cleanups.resize(type); }
cleanups[type - 1] = f; }

ptr alloc() {
cell *const p = new cell{ };
full_range.push_back(p);
return ptr(p); }

void mark(std::unordered_set<cell *> &s, cell *c) {
std::stack<cell *> stack;
stack.push(c);
while (!stack.empty()) {
  cell *current = stack.top();
  stack.pop();
  if (s.find(current) != s.end()) {
    continue; }
  s.insert(current);
  for (const auto f : current->fields) {
    if (f.type == 0 && f.value) {
      stack.push(reinterpret_cast<cell *>(f.value)); } } } }

void sweep(cell *c) {
for (const auto f : c->fields) {
if (f.type > 0) {
  cleanups[f.type - 1](f.value); } }
delete c; }

void cycle() {
std::unordered_set<cell *> s;
s.max_load_factor(0.5);
std::for_each(live_range.begin(), live_range.end(), [&s](cell *x) -> void {
  mark(s, x); });
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