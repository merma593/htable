#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>

extern void *emalloc(size_t);
extern void *erelloc(void *, size_t);
extern int getword(char *s, int limit, FILE *);


#endif
