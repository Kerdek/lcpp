#ifndef MICROGC_GC_HPP
#define MICROGC_GC_HPP

#include <cstddef>
#include <vector>

namespace gc {

struct field {
size_t value;
size_t type; };

struct cell {
std::vector<field> fields; };

struct ptr {
ptr();
ptr(cell *i);
ptr(size_t);
ptr(ptr const &);
ptr(ptr &&);
ptr &operator=(ptr const &);
ptr &operator=(ptr &&);
~ptr();
cell *i;
operator bool() const;
operator size_t() const; };

extern ptr const null;

ptr alloc();
void set_cleanup(size_t type, void (*cb)(size_t));
void cycle();
void help();

}

#endif