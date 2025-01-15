#ifndef GC_STRCLONE_HPP
#define GC_STRCLONE_HPP

#include <cstdlib>
#include <cstring>

inline char *strclone(char const *p) {
char *q = reinterpret_cast<char *>(malloc(strlen(p) + 1));
strcpy(q, p);
return q; }

#endif