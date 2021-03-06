#ifndef CG_H
#define CG_H

#include "parse.h"

void generate(FILE *out, const char *name, struct TokenStream toks);

void gen_preamble(FILE *out, const char *name);
void gen_postamble(FILE *out);

#endif // cg.h
