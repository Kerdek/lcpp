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

cell *alloc();
void set_root(cell *p);
void set_cleanup(size_t type, void (*cb)(size_t));
void cycle();
void help();

}

#endif